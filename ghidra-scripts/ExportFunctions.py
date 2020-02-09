#!python2
# Export functions
# @author Strackeror
# @category MH


import ghidra
import json
import os
import StringIO
import base64

from ghidra.app.plugin.core.searchmem.mask import *
from java.io import StringWriter

json_dict = {
    "functions": {},
    "symbols": {}
}
refcount = {}
symbolTable = currentProgram.getSymbolTable()
namespace = symbolTable.getNamespace("MH", currentProgram.getGlobalNamespace())
functionManager = currentProgram.getFunctionManager()
dataTypeManager = currentProgram.getDataTypeManager()

def buildSearchString(instructions, maxVal):
    search = ""
    for inst in instructions:
        full_instruction = True
        
        for i in range(inst.getNumOperands()):
            for o in inst.getOpObjects(i):
                if isinstance(o, ghidra.program.model.scalar.Scalar):
                    if (o.getValue() > maxVal):
                        full_instruction &= False
                elif isinstance(o, ghidra.program.model.lang.Register):
                    full_instruction &= True
                else:
                    full_instruction &= False
        if full_instruction:
            for b in inst.getBytes():
                search += "{0:02x} ".format(b + 256 if b < 0 else b)
        else:
            b = inst.getBytes()[0]
            search += "{0:02x} ".format(b + 256 if b < 0 else b)
            search += "?? " * (len(inst.getBytes()) - 1)
    return search

def buildSearchVals(instructions, maxVal):
    value_bytes = []
    value_mask = []
    for inst in instructions:
        prototype = inst.getPrototype()
        inst_bytes = inst.getBytes()
        inst_mask = prototype.getInstructionMask().getBytes()
        for i in range(inst.getNumOperands()):
            include_mask = True
            for o in inst.getOpObjects(i):
                if isinstance(o, ghidra.program.model.lang.Register):
                    pass
                elif isinstance(o, ghidra.program.model.scalar.Scalar) and abs(o.getValue()) < maxVal:
                    pass
                else:
                    include_mask = False
            if (include_mask):
                inst_mask = [a | b for (a,b) in zip(inst_mask, prototype.getOperandValueMask(i).getBytes())]
        value_bytes += inst_bytes
        value_mask += inst_mask
    return {
        "value":value_bytes,
        "mask":value_mask
    }


def buildRefList(instructions):
    refs = {}
    for i in range(len(instructions)):
        inst = instructions[i]
        for operand_id in range(inst.getNumOperands()):
            for operand_object_id in range(len(inst.getOpObjects(operand_id))):
                ref = {}
                op_obj = inst.getOpObjects(operand_id)[operand_object_id]
                if isinstance(op_obj, ghidra.program.model.address.GenericAddress) and symbolTable.hasSymbol(op_obj):
                    symbol = symbolTable.getSymbols(op_obj)[0]
                    if symbol.getParentNamespace() == namespace:
                        ref["name"] = symbol.getName()
                        ref["instruction"] = i
                        ref["operand"] = operand_id
                        ref["operand_object"] = operand_object_id
                        ref["type"] = "address"
                    elif functionManager.getFunctionAt(op_obj) is not None:
                        function = functionManager.getFunctionAt(op_obj)
                        function = function.getThunkedFunction(True)
                        if function is not None and function.getParentNamespace() == namespace:
                            ref["name"] = function.getName()
                            ref["instruction"] = i
                            ref["operand"] = operand_id
                            ref["operand_object"] = operand_object_id
                            ref["type"] = "thunked"
                elif isinstance(op_obj, ghidra.program.model.scalar.Scalar) and symbolTable.hasSymbol(toAddr(op_obj.getValue())):
                    symbol = symbolTable.getSymbols(toAddr(op_obj.getValue()))[0]
                    if symbol and symbol.getParentNamespace() == namespace:
                        ref["name"] = symbol.getName()
                        ref["instruction"] = i
                        ref["operand"] = operand_id
                        ref["operand_object"] = operand_object_id
                        ref["type"] = "scalar"
                if len(ref):
                    name = ref["name"]
                    refs[name] = ref
                    if name in refcount:
                        refcount[name] += 1
                    else:
                        refcount[name] = 1
    return refs


def handleFunction(function):
    function_dict = {}

    proto = function.getPrototypeString(False, False)
    if (proto != "undefined {0}()".format(function.getName())):
        function_dict["prototype"] = function.getPrototypeString(False, False)
    function_dict["custom"] = function.hasCustomVariableStorage()
    function_dict["tags"] = [a.getName() for a in function.getTags()]
    if 'OBFUSCATED' in function_dict["tags"]:
        json_dict["functions"][function.getName()] = function_dict
        return

    instructions = []
    instruction_bytes = []
    body = function.getBody()
    inst = getFirstInstruction(function)
    while inst is not None and body.contains(inst.address):
        by = [(i + 256 if i < 0 else i) for i in inst.getBytes()]
        instruction_bytes.append(by)
        instructions.append(inst)
        inst = inst.getNext()
    
    function_dict["references"] = buildRefList(instructions)
    function_dict["search"] = buildSearchVals(instructions, 0x0)

    json_dict["functions"][function.getName()] = function_dict

def handleSymbol(symbol):
    symbol_dict = {}
    json_dict["symbols"][symbol.getName()] = symbol_dict

def handleStructs():
    sio = StringWriter()
    sio.write("a")
    writer = ghidra.program.model.data.DataTypeWriter(dataTypeManager, sio)
    mon = ghidra.util.task.DummyCancellableTaskMonitor()
    writer.write(dataTypeManager.getCategory(ghidra.program.model.data.CategoryPath("/MH")), mon)
    json_dict["dataTypes"] = sio.toString()


targetName = str(askFile("Export file", "Choose export file"))
targetFile = open(targetName, 'w')

for symbol in symbolTable.getSymbols(namespace):
    print(symbol, symbol.address)
    if functionManager.getFunctionAt(symbol.address) is not None:
        handleFunction(functionManager.getFunctionAt(symbol.address))
    else:
        handleSymbol(symbol)

for name in json_dict["functions"]:
    func_dict = json_dict["functions"][name]
    if name in refcount:
        func_dict["refcount"] = refcount[name]
    else:
        func_dict["refcount"] = 0


json.dump(json_dict, targetFile, indent=2)
#print(json.dumps(json_dict["functions"][0], indent=2))

