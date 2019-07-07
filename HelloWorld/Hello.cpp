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
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/CFG.h"
#include<bits/stdc++.h>
using namespace llvm;

#define DEBUG_TYPE "hello"

STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Hello : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++HelloCounter;
      errs() << "Hello: ";
      errs().write_escaped(F.getName()) << '\n';
      return false;
    }
  };
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass");

namespace {
  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct Hello2 : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello2() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      unsigned int basicBlockCounter = 0;
      unsigned int instructionCounter = 0;
      for (BasicBlock &bb : F) {
        ++basicBlockCounter;
        for(Instruction &i : bb) {
          ++instructionCounter;
        }
      }
      errs() << "Hello2 is calling \n";
      errs().write_escaped(F.getName()) << "  Basic blocks: " << basicBlockCounter
                                        << ", Instructions: " << instructionCounter << "\n";
      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char Hello2::ID = 0;
static RegisterPass<Hello2>
Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");

namespace {
  struct InstrStats : public FunctionPass {
    static char ID;
    InstrStats() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      unsigned int blockCounter = 0;
      unsigned int maxInstBlockCounter = 0;
      unsigned int minInstBlockCounter = 0;
      for (BasicBlock &bb : F) {
        ++blockCounter;
        unsigned int instrCounter = 0;
        for (Instruction &i : bb) {
          ++instrCounter;
        }
        if (maxInstBlockCounter == 0 || instrCounter > maxInstBlockCounter) {
          maxInstBlockCounter = instrCounter;
        }
        if (minInstBlockCounter == 0 || instrCounter < minInstBlockCounter) {
          minInstBlockCounter = instrCounter;
        }
        errs() << "No of instructions are " << instrCounter << " in basicBlock " << blockCounter << "\n"; 
      }
      errs() << "Total no of Block are " << blockCounter << "\n";
      errs() << "Instruction Stats from ";
      errs().write_escaped(F.getName()) << "\n Max instructions: " << maxInstBlockCounter
                                        << ",  Min instructions: " << minInstBlockCounter << "\n";
      errs() << "--------------------------------------------------------------\n";
      return false;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char InstrStats::ID = 0;
static RegisterPass<InstrStats> 
Z("instats", "Max & Min instructions in BB Pass (with getAnalysisUsage implemented)");

namespace {
  struct BlockStats : public FunctionPass {
    static char ID;
    BlockStats() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      unsigned int maxPreds = 0, minPreds = 0;
      unsigned int maxSucs = 0, minSucs = 0;
      for(BasicBlock &bb : F) {
        unsigned int predCount = 0, sucCount = 0;
        for(BasicBlock *Pred : predecessors(&bb)) {
          ++predCount;
        }
        for(BasicBlock *Succ : successors(&bb)) {
          ++sucCount;
        }

        if(maxPreds == 0 || predCount > maxPreds) maxPreds = predCount;
        if(minPreds == 0 || predCount < minPreds) minPreds = predCount;
        if(maxSucs == 0 || sucCount > maxSucs) maxSucs = sucCount;
        if(minSucs == 0 || sucCount < minSucs) minSucs = sucCount;

      }
      errs().write_escaped(F.getName()) << "\nPredecessors stats: "  
             << "MAX COUNT: " << maxPreds << "\t"
             << "MIN COUNT: " << minPreds << "\n";

      errs() << "Successors stats: " << "MAX COUNT: " << maxSucs << "\t"
                                     << "MIN COUNT: " << minSucs << "\n";
      errs() << "---------------------------------------------------------------\n";
      return false;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }

  };

}

char BlockStats :: ID = 0;
static RegisterPass<BlockStats>
A("blockstats", "Block with max/min predecessors");