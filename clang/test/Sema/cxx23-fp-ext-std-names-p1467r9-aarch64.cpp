// RUN: %clang_cc1 -fsyntax-only -std=c++23 -triple aarch64-linux-gnu -verify -ast-dump %s | FileCheck %s
// Test extended floating-point types on aarch64 where double == long double (IEEE double-precision)

_Float16 f16_val = 1.0f16;
//CHECK:      VarDecl {{.*}} f16_val '_Float16' cinit
//CHECK-NEXT: FloatingLiteral {{.*}} '_Float16' 1.000000e+00

// On aarch64, long double is the same as double (IEEE double-precision)
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

// Test overload resolution with double == long double
int f(float) { return 1; } // expected-note {{candidate function}}
int f(double) { return 2; } // expected-note {{candidate function}}

_Float16 float16_val = 1.0f16;
float float_val = 1.0f;

int test1 = f(float16_val); // expected-error {{call to 'f' is ambiguous}}

int f_2(long double) { return 1; }
int test2 = f_2(float16_val);
//CHECK:      VarDecl {{.*}} test2 'int' cinit
//CHECK-NEXT: CallExpr {{.*}} 'int'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'int (*)(long double)' <FunctionToPointerDecay>
//CHECK-NEXT: DeclRefExpr {{.*}} 'int (long double)' lvalue Function {{.*}} 'f_2' 'int (long double)'
//CHECK-NEXT: ImplicitCastExpr {{.*}} 'long double' <FloatingCast>
//CHECK-NEXT: ImplicitCastExpr {{.*}} '_Float16' <LValueToRValue>
