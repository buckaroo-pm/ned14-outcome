+++
title = "`OUTCOME_TRYV(expr)/OUTCOME_TRY(expr)`"
description = "Evaluate an expression which results in a type matching the `ValueOrError<void, E>` concept, continuing execution if successful, immediately returning `E` from the calling function if unsuccessful."
+++

Evaluate an expression which results in a type matching the {{% api "ValueOrError<T, E>" %}} concept, continuing execution if successful, immediately returning `E` from the calling function if unsuccessful.

The difference between the `OUTCOME_TRYV(expr)` and `OUTCOME_TRY(expr)` editions is that the latter will set a variable if two or more macro arguments are present (see {{% api "OUTCOME_TRY(var, expr)" %}}). The former requires the `T` to be `void`.

*Overridable*: Not overridable.

*Definition*: Firstly the expression's temporary is bound to a uniquely named, stack allocated, `auto &&`. If that reference's bound object's `.has_value()` is false, immediately execute `return try_operation_return_as(propagated unique reference);`, propagating the rvalue/lvalue/etc-ness of the original expression.

{{% api "try_operation_return_as(expr)" %}} is a customisation point, the default implementation of which returns a {{% api "failure<E>" %}} for Outcome types, or an {{% api "std::unexpected<E>" %}} for Expected types.

*Header*: `<outcome/try.hpp>`