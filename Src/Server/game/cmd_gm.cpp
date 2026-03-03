// Only if you have this system: https://metin2.dev/topic/10208-expanded-reload-commands/

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
					ch->ChatPacket(CHAT_TYPE_INFO, "Reloading: SpecialItemGroup: %s", szSpecialItemGroupFileName);
					if (!ITEM_MANAGER::instance().ReadSpecialDropItemFile(szSpecialItemGroupFileName, true))
						ch->ChatPacket(CHAT_TYPE_INFO, "failed to reload SpecialItemGroup: %s", szSpecialItemGroupFileName);
					else
						ch->ChatPacket(CHAT_TYPE_INFO, "reload success: SpecialItemGroup: %s", szSpecialItemGroupFileName);
// add after:
#ifdef ENABLE_LEGENDARY_CHEST
					ch->ChatPacket(CHAT_TYPE_INFO, "Reloading: LegendaryChestFile: %s", szLegendaryChestFileName);
					if (!ITEM_MANAGER::instance().ReadLegendaryChestItemGroup(szLegendaryChestFileName, true))
						ch->ChatPacket(CHAT_TYPE_INFO, "failed to reload LegendaryChestFile: %s", szLegendaryChestFileName);
					else
						ch->ChatPacket(CHAT_TYPE_INFO, "reload success: LegendaryChestFile: %s", szLegendaryChestFileName);
#endif
