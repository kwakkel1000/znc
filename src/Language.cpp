/*
 * Copyright (C) 2004-2011  See the AUTHORS file for details.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 */

#include <znc/Language.h>
#include <znc/FileUtils.h>
#include <znc/znc.h>
#include <znc/ZNCDebug.h>
#include <stack>
#include <sstream>

CLanguage::CLanguage()
{
	LanguageKeyMap tmp1;
	LanguageWhoMap tmp2;
	LanguageMap tmp3;
	tmp1["key1"]="value1";
	tmp2["test"]=tmp1;
	tmp3["EN"]=tmp2;
}

bool CLanguage::GetKey(const CString& sLanguage, const CString& sWho, const CString& sKey, CString& sRes, const CString& sDefault = "") {
	sRes = sDefault;

	LanguageMap::iterator LanguageMapIt = m_LanguageKeys.find(sLanguage);
	if (LanguageMapIt == m_LanguageKeys.end() || LanguageMapIt->second.empty())
		return false;

	LanguageWhoMap::iterator LanguageWhoMapIt = LanguageMapIt->second.find(sWho);
	if (LanguageWhoMapIt == LanguageMapIt->second.end() || LanguageWhoMapIt->second.empty())
		return false;

	LanguageKeyMap::iterator LanguageKeyMapIt = LanguageWhoMapIt->second.find(sKey);
	if (LanguageKeyMapIt == LanguageWhoMapIt->second.end() || LanguageKeyMapIt->second.empty())
		return false;

	sRes = LanguageKeyMapIt->second;
	return true;
}

void CLanguage::GetLanguageFiles(VCString& vRet) const {
	vRet.clear();

	CString sModuleRoot(CZNC::Get().GetModPath());
	sModuleRoot.TrimRight("/");

	if (!sModuleRoot.empty()) {
		sModuleRoot += "/";
	}

	if (!sModuleRoot.empty() && CFile::IsDir(sModuleRoot)) {
		CDir Dir(sModuleRoot);

		for (unsigned int d = 0; d < Dir.size(); d++) {
			const CFile& SubDir = *Dir[d];

			if (SubDir.IsDir() && SubDir.GetShortName() == "_default_") {
				vRet.push_back(SubDir.GetShortName());
				DEBUG(SubDir.GetShortName());
				break;
			}
		}

		for (unsigned int e = 0; e < Dir.size(); e++) {
			const CFile& SubDir = *Dir[e];

			if (SubDir.IsDir() && SubDir.GetShortName() != "_default_" && SubDir.GetShortName() != ".svn") {
				vRet.push_back(SubDir.GetShortName());
				DEBUG(SubDir.GetShortName());
			}
		}
	}
}
