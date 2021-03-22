#pragma once

#include "datatype_base.h"

#define ENUMERATOR(name, value)  const static int E_##name = value;     \
    inline const enum_type & Set##name() { return SetValue(E_##name); } \
    inline bool Is##name() const { return m_Value == E_##name; }

#define ENUMSETTEXT(enumvalue, text) int temp_##enumvalue = enumvalue; \
    TextsMap[temp_##enumvalue] = text;


namespace common
{
	template<class T>
	class DataTypeEnum
	    : public DataTypeBase<int, T>
	{
	public:
        using DataTypeBase<int, T>::m_Value;
        typedef typename DataTypeBase<int, T>::fund_type fund_type;
		typedef std::map<int, std::string> EnumTextsMap;

		typedef T enum_type;

		static void InitTexts(EnumTextsMap &TextsMap)
		{
		}

		static const EnumTextsMap & __GetTextsMap()
		{
			static EnumTextsMap _TextsMap;
			static bool _bInited;
			if (!_bInited)
			{
				T::InitTexts(_TextsMap);
				_bInited = true;
			}
			return _TextsMap;
		}

		static std::list<std::string> GetTexts()
		{
			const EnumTextsMap &TextsMap = __GetTextsMap();
			std::list<std::string> texts;
			for (EnumTextsMap::const_iterator it = TextsMap.begin(); it != TextsMap.end(); ++it)
			{
				texts.push_back(it->second);
			}
			return texts;
		}

		std::string GetText() const
		{
			const EnumTextsMap &TextsMap = __GetTextsMap();
			EnumTextsMap::const_iterator it = TextsMap.find(m_Value);
			return (it != TextsMap.end())?it->second:to_str(m_Value);
		}

		bool SetText(const std::string &str)
		{
			const EnumTextsMap &TextsMap = __GetTextsMap();
			for (EnumTextsMap::const_iterator it = TextsMap.begin(); it != TextsMap.end(); ++it)
			{
				if (it->second == str)
				{
					m_Value = it->first;
					return true;
				}
			}
			m_Value = my_cast<fund_type>(str);
			return false;
		}

		inline std::string ValueToString() const
		{
			return GetText();
		}

		inline T& ValueFromString(const std::string &str)
		{
			SetText(str);
			return *static_cast<T*>(this);
		}
	};
}
