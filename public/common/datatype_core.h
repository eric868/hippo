#pragma once
#include <assert.h>
#include "datatype_basic.h"

namespace common
{
	struct TypeUserid : public DataTypeString<TypeUserid, 64>
	{
		TypeUserid() {}
		TypeUserid(const char* userid)
		{
			SetValue(userid);
		}
		TypeUserid(const std::string& userid)
		{
			SetValue(userid);
		}
	};

	class TypePrice : public DataTypeDecimal<TypePrice>
	{
	public:
		TypePrice() {};
		TypePrice(double Price)
		{
			SetValue(Price);
		}
	};

	class TypeVolume : public DataTypeInt<TypeVolume>
	{
	public:
		TypeVolume() {};
		TypeVolume(unsigned Volume)
		{
			SetValue(Volume);
		}
		TypeVolume GetNegative() const
		{
			return TypeVolume().SetValue(-m_Value);
		}
	};

	struct EnumDirection : public DataTypeEnum<EnumDirection>
	{
		ENUMERATOR(All, 'a');
		ENUMERATOR(Buy, '0');
		ENUMERATOR(Sell, '1');

		EnumDirection()
		{
			m_Value = E_Buy;
		}

		static void InitTexts(EnumTextsMap &TextsMap)
		{
			ENUMSETTEXT(E_Buy, "买　");
			ENUMSETTEXT(E_Sell, "　卖");
		}

		EnumDirection GetNegative() const
		{
			if (IsBuy())
				return EnumDirection().SetSell();
			else
				return EnumDirection().SetBuy();
		}
	};
	struct EnumExchangeID : public DataTypeEnum<EnumExchangeID>
	{
		ENUMERATOR(SHFE, 1);
		ENUMERATOR(DCE, 2);
		ENUMERATOR(CZCE, 3);
		ENUMERATOR(CFFEX, 4);
		ENUMERATOR(INE, 5);
		ENUMERATOR(SSE, 6);
		ENUMERATOR(SZSE, 7);

		EnumExchangeID() {m_Value = E_SHFE;}
		static void InitTexts(EnumTextsMap &TextsMap)
		{
			ENUMSETTEXT(E_SHFE, "上期所");
			ENUMSETTEXT(E_DCE, "大商所");
			ENUMSETTEXT(E_CZCE, "郑商所");
			ENUMSETTEXT(E_CFFEX, "中金所");
			ENUMSETTEXT(E_INE, "能源所");
			ENUMSETTEXT(E_SSE, "上交所");
			ENUMSETTEXT(E_SZSE, "深交所");
		}
		std::string GetCode() const
		{
			if (IsSHFE()) {
				return "SHFE";
			}
			else if (IsDCE()) {
				return "DCE";
			}
			else if (IsCZCE()) {
				return "CZCE";
			}
			else if (IsCFFEX()) {
				return "CFFEX";
			}
			else if (IsINE()) {
				return "INE";
			}
			else if (IsSSE()) {
				return "SSE";
			}
			else if (IsSZSE()) {
				return "SZSE";
			}
			return std::string();
		}
		EnumExchangeID &SetCode(const std::string &code)
		{
			if (code == "DCE")  {
				SetDCE();
			}
			else if (code == "CZCE") {
				SetCZCE();
			}
			else if (code == "SHFE") {
				SetSHFE();
			}
			else if (code == "CFFEX") {
				SetCFFEX();
			}
			else if (code == "INE") {
				SetINE();
			}
			else if (code == "SSE") {
				SetSSE();
			}
			else if (code == "SZSE") {
				SetSZSE();
			}
			else {
				assert(false);
			}
			return *this;
		}
	};

};

