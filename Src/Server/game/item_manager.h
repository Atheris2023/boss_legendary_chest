// 1. Search for:
class CLevelItemGroup
// add BEFORE:
#ifdef ENABLE_LEGENDARY_CHEST
class CLegendaryChestGroup
{
	struct SLegendaryItemGroupInfo
	{
		DWORD	dwVnum;
		DWORD	dwPct;
		int	iCount;

		SLegendaryItemGroupInfo(DWORD dwVnum, DWORD dwPct, int iCount)
			: dwVnum(dwVnum), dwPct(dwPct), iCount(iCount)
			{}
	};

	public:
	CLegendaryChestGroup(DWORD dwVnum, DWORD dwMobVnum, const std::string& r_stName)
		:
		m_dwVnum(dwVnum),
	m_dwMobVnum(dwMobVnum),
	m_stName(r_stName)
	{
	}

	const std::vector<SLegendaryItemGroupInfo> & GetVector()
	{
		return m_vec_items;
	}

	void AddItem(DWORD dwItemVnum, DWORD dwPct, int iCount)
	{
		m_vec_items.emplace_back(SLegendaryItemGroupInfo(dwItemVnum, dwPct, iCount));
	}

	private:
	[[maybe_unused]] DWORD m_dwVnum;
	[[maybe_unused]] DWORD m_dwMobVnum;
	std::string m_stName;
	std::vector<SLegendaryItemGroupInfo> m_vec_items;
};
#endif

// 2. Search for:
		bool			ReadSpecialDropItemFile(...);
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
		bool			ReadLegendaryChestItemGroup(const char * c_pszFileName, bool isReloading = false);
#endif

// 3. Search for:
		std::map<DWORD, CSpecialItemGroup*> m_map_pkSpecialItemGroup;
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
		std::map<DWORD, CLegendaryChestGroup*> m_map_pkLegendaryItemGroup;
#endif
