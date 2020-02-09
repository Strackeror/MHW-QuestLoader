# Import functions
# @author Strackeror
# @category MH

import json
import ghidra
import time


from ghidra.app.plugin.core.searchmem.mask import *

symbolTable = currentProgram.getSymbolTable()
namespace = symbolTable.getNamespace("MH", currentProgram.getGlobalNamespace())
if namespace is None:
    namespace = symbolTable.createNameSpace(currentProgram.getGlobalNamespace(), "MH", ghidra.program.model.symbol.SourceType.USER_DEFINED)

monitor = ghidra.util.task.TaskMonitor.DUMMY

targetName = str(askFile("Export file", "Choose export file"))
targetFile = open(targetName, 'r')
json_dict = json.load(targetFile)

def maskedSearch(values, mask, addr_set = None):
    search_data =ghidra.app.plugin.core.searchmem.SearchData.createSearchData("search", values, mask)
    search_info = ghidra.util.search.memory.SearchInfo(search_data, 2, True, True, 1, False, None)
    select = ghidra.program.util.ProgramSelection(currentProgram.getMinAddress(), currentProgram.getMaxAddress())
    if addr_set is not None:
        select = ghidra.program.util.ProgramSelection(addr_set)
    alg = search_info.createSearchAlgorithm(currentProgram, currentProgram.getMinAddress(), select)
    acc = ghidra.util.datastruct.ListAccumulator()
    alg.search(acc, monitor)
    return [i.getAddress() for i in acc]

def disassembleFunc(addr):
    print "disassembling",addr
    ghidra.app.cmd.disassemble.DisassembleCommand(addr, None, True).applyTo(currentProgram, monitor)

def handleReferences(function, ref_dic):
    instructions = []
    instruction = getFirstInstruction(function)
    while function.getBody().contains(instruction.address):
        instructions += [instruction]
        instruction = instruction.getNext()
        if instruction is None:
            break

    for refname in ref_dic:
        if refname in functions or refname in symbols:
            continue
        ref = ref_dic[refname]
        print "finding", ref,
        instruction_index = ref["instruction"]
        operand_id = ref["operand"]
        operand_obj_id = ref["operand_object"]
        ref_type = ref["type"]
        try:
            target_obj = instructions[instruction_index].getOpObjects(operand_id)[operand_obj_id]
        except:
            print ""
            continue
        print target_obj

        addr = None
        if ref_type == "address":
            addr = target_obj
        elif ref_type == "scalar":
            addr = toAddr(target_obj.getValue())
        elif ref_type == "thunked":
            disassembleFunc(target_obj)
            function = createFunction(target_obj, None)
            addr = function.getThunkedFunction(False).getEntryPoint()
        if addr is None:
            continue

        if refname in json_dict["functions"]:
            handleFunction(addr, refname, True)
        elif refname in json_dict["symbols"]:
            handleSymbol(addr, refname)

functions = {}
symbols = {}

def handleSymbol(addr, name):
    print "handling symbol",addr,name
    symbol = createSymbol(addr, name, False)
    if symbol is None:
        return
    symbol.setNamespace(namespace)
    symbols[name] = symbol

def handleFunction(addr, name, recheck = False):
    print "handling function",addr,name
    disassembleFunc(addr)
    func = createFunction(addr, name)
    if func is None:
        func = getFunctionAt(addr)
        if func is None:
            return
        func.setName(name, ghidra.program.model.symbol.SourceType.USER_DEFINED)

    func.getSymbol().setNamespace(namespace)
    func_dict = json_dict["functions"][name]
    functions[name] = func

    if "prototype" in func_dict:
        parser = ghidra.app.util.parser.FunctionSignatureParser(currentProgram.getDataTypeManager(), ghidra.app.plugin.core.analysis.DefaultDataTypeManagerService())
        sig = parser.parse(func.getSignature(), func_dict["prototype"])
        ghidra.app.cmd.function.ApplyFunctionSignatureCmd(func.getEntryPoint(), sig, ghidra.program.model.symbol.SourceType.USER_DEFINED).applyTo(currentProgram, monitor)
        print "setting",(sig.getPrototypeString())

    tags = func_dict["tags"]
    for tag in tags:
        func.addTag(tag)
    if 'OBFUSCATED' in tags:
        print 'Skipping obfuscated function'
        return
    if recheck:
        print "rechecking",
        search = func_dict["search"]
        res = maskedSearch(search["value"], search["mask"], func.getBody())
        if len(res) != 1:
            print "failure"
            return
        print "success"
    handleReferences(func,func_dict["references"])

function_order = json_dict["functions"].items()
function_order.sort(key = lambda (_, fd): fd["refcount"])

for name, func in function_order:
    if name in functions or 'OBFUSCATED' in func["tags"]:
        continue
    print "searching for", name,
    addrs = maskedSearch(func["search"]["value"], func["search"]["mask"])
    if len(addrs) != 1:
        print 'function not found'
        continue
    print 'function found'
    handleFunction(addrs[0], name)


for name in json_dict["functions"]:
    if name not in functions:
        print name, "NOT FOUND"

