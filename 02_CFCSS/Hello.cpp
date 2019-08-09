//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"
using namespace llvm;

// Control Flow Checking by Software Signatures
namespace {
  struct CFCSS : public ModulePass {
    static char ID;
    CFCSS() : ModulePass(ID) {}

    static LLVMContext &Context = getGlobalContext();

    GlobalVariable *createGlob(Module &M, IRBuilder <> &Builder, std::string Name) {
    	M.getOrInsertGlobal(Name, Builder.getInt32Ty());
   		GlobalVariable *gVar = M.getNamedGlobal(Name);
   		gVar->setLinkage(GlobalValue::ExternalLinkage);
   		gVar->setAlignment(6);
   		return gVar;
    }

    bool runOnModule(Module &M) {
    	static LLVMContext &Context = getGlobalContext();
    	static IRBuilder<> Builder(Context);
   		GlobalVariable *gVar = createGlob(M, Builder, "GlobVar");
   		return true;
    }
  };
}

char CFCSS :: ID = 0;
static RegisterPass<CFCSS>
CF("cfcss", "Control Flow Checking by Software Signatures");