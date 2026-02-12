// RUN: %clang_cc1 -fsyntax-only -std=c++23 -triple powerpc64-linux-gnu -verify -ast-dump %s | FileCheck %s
// Test extended floating-point types on powerpc64 where long double == ppc_fp128

_Float16 f16_val = 1.0f16;
//CHECK:      VarDecl {{.*}} f16_val '_Float16' cinit
//CHECK-NEXT: FloatingLiteral {{.*}} '_Float16' 1.000000e+00

// On powerpc64, long double uses the IBM double-double format (ppc_fp128)
// Test that conversions work correctly
float f_val = 1.0f16;
//CHECK:      VarDecl {{.*}} f_val 'float' cinit
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'float' <FloatingCast>
//CHECK-NEXT: FloatingLiteral {{.*}} '_Float16' 1.000000e+00

double d_val = 1.0f16;
//CHECK:      VarDecl {{.*}} d_val 'double' cinit
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'double' <FloatingCast>
//CHECK-NEXT: FloatingLiteral {{.*}} '_Float16' 1.000000e+00

long double ld_val = 1.0f16;
//CHECK:      VarDecl {{.*}} ld_val 'long double' cinit
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'long double' <FloatingCast>
//CHECK-NEXT: FloatingLiteral {{.*}} '_Float16' 1.000000e+00

// Test that float and double can be converted to ppc_fp128 long double
int f(long double) { return 1; }

float float_val = 1.0f;
double double_val = 1.0;

int test1 = f(float_val);
//CHECK:      VarDecl {{.*}} test1 'int' cinit
//CHECK-NEXT: CallExpr {{.*}} 'int'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'int (*)(long double)' <FunctionToPointerDecay>
//CHECK-NEXT: DeclRefExpr {{.*}} 'int (long double)' lvalue Function {{.*}} 'f' 'int (long double)'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'long double' <FloatingCast>

int test2 = f(double_val);
//CHECK:      VarDecl {{.*}} test2 'int' cinit
//CHECK-NEXT: CallExpr {{.*}} 'int'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'int (*)(long double)' <FunctionToPointerDecay>
//CHECK-NEXT: DeclRefExpr {{.*}} 'int (long double)' lvalue Function {{.*}} 'f' 'int (long double)'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'long double' <FloatingCast>

// expected-no-diagnostics
