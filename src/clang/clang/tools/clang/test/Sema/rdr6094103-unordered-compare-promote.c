// RUN: clang-cc -ast-dump %s 2>&1 | grep ImplicitCastExpr | count 2

int foo (double x, long double y) {
  // There needs to be an implicit cast on x here.
  return __builtin_isgreater(x, y);
}
