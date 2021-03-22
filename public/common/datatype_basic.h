#pragma once

#include "datatype_base.h"
#include "datatype_base_ext.h"

namespace common
{
class TypeBool                    : public DataTypeBool<TypeBool> {};
class TypeString                  : public DataTypeString<TypeString, 256> {};
class TypeDouble                  : public DataTypeDouble<TypeDouble> {};
class TypeUInt                    : public DataTypeUint<TypeUInt> {};
class TypeInt                     : public DataTypeInt<TypeInt> {};
class TypeDateString              : public DataTypeString<TypeDateString, 8> {};
class TypeTimeString              : public DataTypeString<TypeTimeString, 8> {};
class TypePercent                 : public DataTypeDecimal<TypePercent>{};
}

