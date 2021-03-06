//===--- Mangle.h - Mangle C++ Names ----------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements C++ name mangling according to the Itanium C++ ABI,
// which is used in GCC 3.2 and newer (and many compilers that are
// ABI-compatible with GCC):
//
//   http://www.codesourcery.com/public/cxx-abi/abi.html
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_CODEGEN_MANGLE_H
#define LLVM_CLANG_CODEGEN_MANGLE_H

#include "CGCXX.h"

namespace llvm {
  class raw_ostream;
}

namespace clang {
  class ASTContext;
  class CXXConstructorDecl;
  class CXXDestructorDecl;
  class NamedDecl;
  class VarDecl;
  
  bool mangleName(const NamedDecl *D, ASTContext &Context, 
                  llvm::raw_ostream &os);
  void mangleGuardVariable(const VarDecl *D, ASTContext &Context,
                           llvm::raw_ostream &os);
  void mangleCXXCtor(const CXXConstructorDecl *D, CXXCtorType Type,
                     ASTContext &Context, llvm::raw_ostream &os);
  void mangleCXXDtor(const CXXDestructorDecl *D, CXXDtorType Type,
                     ASTContext &Context, llvm::raw_ostream &os);
}

#endif 
