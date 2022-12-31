#include "optional.h"

using OptionalInt = ::Template::Optional<int>;

struct IntStruct {
  int i_;
  IntStruct(int i) : i_(i) {}
  IntStruct() : IntStruct(-1) {}
  ~IntStruct() = default;
};
using OptionalIntStruct = ::Template::Optional<IntStruct>;

void foo(void const *);
void bar()
{
  //OptionalInt emptyOptionalInt_1(OptionalInt::EMPTY_v);
  //foo( (void const *) &emptyOptionalInt_1);

  OptionalInt emptyOptionalInt_2(OptionalInt::EMPTY{});
  foo( (void const *) &emptyOptionalInt_2);

  const auto auto_optionalIntDefault = OptionalInt();
  foo( (void const *) &auto_optionalIntDefault);

  OptionalInt optionalIntDefault;
  foo( (void const *) &optionalIntDefault);

  OptionalInt optionalInt1(1);
  foo( (void const *) &optionalInt1);

  //OptionalIntStruct emptyOptionalIntStruct_1(OptionalIntStruct::EMPTY_v);
  //foo( (void const *) &emptyOptionalIntStruct_1);

  OptionalIntStruct emptyOptionalIntStruct_2(OptionalIntStruct::EMPTY{});
  foo( (void const *) &emptyOptionalIntStruct_2);

  const auto auto_OptionalIntStructDefault = OptionalIntStruct();
  foo( (void const *) &auto_OptionalIntStructDefault);

  OptionalIntStruct optionalIntStructDefault;
  foo( (void const *) &optionalIntStructDefault);

  OptionalIntStruct optionalIntStruct1( IntStruct(1) );
  foo( (void const *) &optionalIntStruct1);
}
