#ifndef POINCARE_MATRIX_RREF_H
#define POINCARE_MATRIX_RREF_H

#include <poincare/expression.h>

namespace Poincare {

class MatrixRrefNode final : public ExpressionNode {
public:

  // TreeNode
  size_t size() const override { return sizeof(MatrixRrefNode); }
  int numberOfChildren() const override;
#if POINCARE_TREE_LOG
  void logNodeName(std::ostream & stream) const override {
    stream << "MatrixRref";
  }
#endif

  // Properties
  Type type() const override { return Type::MatrixRref; }
private:
  // Layout
  Layout createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  // Simplification
  Expression shallowReduce(ReductionContext reductionContext) override;
  LayoutShape leftLayoutShape() const override { return LayoutShape::MoreLetters; };
  LayoutShape rightLayoutShape() const override { return LayoutShape::BoundaryPunctuation; }
  // Evaluation
  Evaluation<float> approximate(SinglePrecision p, Context * context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const override { return templatedApproximate<float>(context, complexFormat, angleUnit); }
  Evaluation<double> approximate(DoublePrecision p, Context * context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const override { return templatedApproximate<double>(context, complexFormat, angleUnit); }
  template<typename T> Evaluation<T> templatedApproximate(Context * context, Preferences::ComplexFormat complexFormat, Preferences::AngleUnit angleUnit) const;
};

class MatrixRref final : public Expression {
public:
  MatrixRref(const MatrixRrefNode * n) : Expression(n) {}
  static MatrixRref Builder(Expression child) { return TreeHandle::FixedArityBuilder<MatrixRref, MatrixRrefNode>({child}); }

  static constexpr Expression::FunctionHelper s_functionHelper = Expression::FunctionHelper("rref", 1, &UntypedBuilderOneChild<MatrixRref>);

  Expression shallowReduce(ExpressionNode::ReductionContext reductionContext);
};

}

#endif