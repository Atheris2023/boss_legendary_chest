// Search for:
bool ITEM_MANAGER::ReadDropItemGroup(const char * c_pszFileName)
// add before:
#ifdef ENABLE_LEGENDARY_CHEST
bool ITEM_MANAGER::ReadLegendaryChestItemGroup(const char * c_pszFileName, bool isReloading)
{
	CTextFileLoader loader;

	if (!loader.Load(c_pszFileName))
		return false;

	std::map<DWORD, CLegendaryChestGroup*> tempLegendaryGr;
	if (isReloading)
		sys_log(0, "RELOADING LegendaryChestGroup");

	for (DWORD i = 0; i < loader.GetChildNodeCount(); ++i)
	{
		std::string stName("");

		loader.GetCurrentNodeName(&stName);

		if (strncmp (stName.c_str(), "kr_", 3) == 0)
			continue;

		loader.SetChildNode(i);

		int iMobVnum = 0;

		if (!loader.GetTokenInteger("mob", &iMobVnum))
		{
			sys_err("ReadLegendaryChestItemGroup : Syntax error %s : no mob vnum, node %s", c_pszFileName, stName.c_str());
			loader.SetParentNode();
			return false;
		}

		sys_log(0,"LEGENDARY_CHEST_GROUP %s %d", stName.c_str(), iMobVnum);

		TTokenVector* pTok = nullptr;

		CLegendaryChestGroup* pkGroup;
		bool bNew = true;
		if (isReloading)
		{
			itertype(tempLegendaryGr) it = tempLegendaryGr.find(iMobVnum);
			if (it == tempLegendaryGr.end())
			{
				pkGroup = M2_NEW CLegendaryChestGroup(0, iMobVnum, stName);
			}
			else
			{
				bNew = false;
				/* CLegendaryChestGroup* */ pkGroup = it->second;
			}
		}
		else
		{
			itertype(m_map_pkLegendaryItemGroup) it = m_map_pkLegendaryItemGroup.find(iMobVnum);
			if (it == m_map_pkLegendaryItemGroup.end())
				pkGroup = M2_NEW CLegendaryChestGroup(0, iMobVnum, stName);
			else
			{
				bNew = false;
				/* CLegendaryChestGroup* */ pkGroup = it->second;
			}
		}

		for (int k = 1; k < 256; ++k)
		{
			char buf[4];
			snprintf(buf, sizeof(buf), "%d", k);

			if (loader.GetTokenVector(buf, &pTok))
			{
				std::string& name = pTok->at(0);
				DWORD dwVnum = 0;

				if (!GetValidVnum(name.c_str(), dwVnum)
					&& !GetVnumByOriginalName(name.c_str(), dwVnum))
				{
					sys_err("ReadLegendaryChestItemGroup : there is no item %s : node %s", name.c_str(), stName.c_str());
					M2_DELETE(pkGroup);
					return false;
				}

				int iCount = 0;
				str_to_number(iCount, pTok->at(1).c_str());

				if (iCount < 1)
				{
					sys_err("ReadLegendaryChestItemGroup : there is no count for item %s : node %s", name.c_str(), stName.c_str());
					M2_DELETE(pkGroup);

					return false;
				}

				float fPercent = atof(pTok->at(2).c_str());

				DWORD dwPct = (DWORD)fPercent;

				sys_log(0,"        name %s pct %d count %d", name.c_str(), dwPct, iCount);
				pkGroup->AddItem(dwVnum, dwPct, iCount);

				continue;
			}

			break;
		}
		if (bNew)
		{
			if (isReloading)
				tempLegendaryGr.emplace(iMobVnum, pkGroup);
			else
				m_map_pkLegendaryItemGroup.emplace(iMobVnum, pkGroup);
		}

		loader.SetParentNode();
	}

	if (isReloading)
	{
		for (std::map<DWORD, CLegendaryChestGroup*>::iterator it = m_map_pkLegendaryItemGroup.begin(); it != m_map_pkLegendaryItemGroup.end(); it++)
			M2_DELETE(it->second);
		m_map_pkLegendaryItemGroup.clear();

		for (std::map<DWORD, CLegendaryChestGroup*>::iterator it = tempLegendaryGr.begin(); it != tempLegendaryGr.end(); it++)
			m_map_pkLegendaryItemGroup[it->first] = it->second;
	}

	return true;
}
#endif
