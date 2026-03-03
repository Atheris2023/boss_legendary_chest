// Search for:
	// MobDropItem Group
	{
		itertype(m_map_pkMobItemGroup) it;
		[...]
	}
// add BEFORE:
#ifdef ENABLE_LEGENDARY_CHEST
	// Legendary Chest Item Group
	{
		itertype(m_map_pkLegendaryItemGroup) it;
		it = m_map_pkLegendaryItemGroup.find(pkChr->GetRaceNum());

		if (it != m_map_pkLegendaryItemGroup.end())
		{
			typeof(it->second->GetVector()) v = it->second->GetVector();

			DWORD vnums[3]{};
			WORD count[3]{};
			int iChances[3]{};

			for (DWORD i = 0; i < v.size(); ++i)
			{
				vnums[i] = v[i].dwVnum;
				count[i] = v[i].iCount;
				iChances[i] = v[i].dwPct;
			}

			int iRandNum = random_number(1, 100);

			int cumulative = 0;

			for (int i = 0; i < 3; ++i)
			{
				cumulative += iChances[i];

				if (iRandNum < cumulative)
				{
					if (test_server)
						pkKiller->ChatPacket(CHAT_TYPE_INFO, "iRandNum: %d, dwVnum: %d", iRandNum, vnums[i]);

					LPITEM item = CreateItem(vnums[i], count[i], 0, true);

					if (item)
						vec_item.emplace_back(item);

					break;
				}
			}
		}
	}
#endif

// == Only if you have Drop Info Target System ==
// Search for:
bool ITEM_MANAGER::CreateDropItemVector(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<std::pair<int,int> > & vec_item)
{
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
	// Legendary Chest Group
	{
		itertype(m_map_pkLegendaryItemGroup) it;
		it = m_map_pkLegendaryItemGroup.find(pkChr->GetRaceNum());

		if ( it != m_map_pkLegendaryItemGroup.end() )
		{
			typeof(it->second->GetVector()) v = it->second->GetVector();

			for (DWORD i = 0; i < v.size(); ++i)
				vec_item.push_back(std::make_pair(v[i].dwVnum, v[i].iCount));
		}
	}
#endif
