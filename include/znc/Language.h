
/*
 * Copyright (C) 2004-2011  See the AUTHORS file for details.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <znc/zncconfig.h>
#include <znc/ZNCString.h>
#include <map>

class CFile;
class CLanguage {
public:
	CLanguage();
	typedef std::map< CString, CString >  LanguageKeyMap;
	typedef std::map< CString, LanguageKeyMap >  LanguageWhoMap;
	typedef std::map< CString, LanguageWhoMap > LanguageMap;
	bool GetKey(const CString& sLanguage, const CString& sWho, const CString& sKey, CString& sRes, const CString& sDefault);
	void GetLanguageFiles(VCString& vRet) const;

private:
	LanguageMap m_LanguageKeys;
};
#endif // !LANGUAGE_H
