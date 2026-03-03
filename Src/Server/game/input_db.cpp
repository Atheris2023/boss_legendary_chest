// 1. Search for:
	char szSpecialItemGroupFileName[FILE_NAME_LEN];
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
	char szLegendaryChestFileName[FILE_NAME_LEN];
#endif

// 2. Search for:
	snprintf(szSpecialItemGroupFileName, sizeof(szSpecialItemGroupFileName),
			"%s/special_item_group.txt", LocaleService_GetBasePath().c_str());
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
	snprintf(szLegendaryChestFileName, sizeof(szLegendaryChestFileName),
			"%s/legendary_chest.txt", LocaleService_GetBasePath().c_str());
#endif

// 3. Search for:
	sys_log(0, "LoadLocaleFile: SpecialItemGroup: %s", szSpecialItemGroupFileName);
	if (!ITEM_MANAGER::instance().ReadSpecialDropItemFile(szSpecialItemGroupFileName))
	{
		sys_err("cannot load SpecialItemGroup: %s", szSpecialItemGroupFileName);
		thecore_shutdown();
		return;
	}
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
	sys_log(0, "LoadLocaleFile: LegendaryChestFile: %s", szLegendaryChestFileName);
	if (!ITEM_MANAGER::instance().ReadLegendaryChestItemGroup(szLegendaryChestFileName))
	{
		sys_err("cannot load LegendaryChestFile: %s", szLegendaryChestFileName);
		thecore_shutdown();
		return;
	}
#endif
