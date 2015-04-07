#include "Textures.hpp"






//loads all textures
void TextureLoading::LoadTextures()
{
	t_menuBackground.loadFromFile("Data/Sprites/Menu2.png");
	t_menuButtonPlay.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(2, 308, 600, 100));
	t_menuButtonOptions.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(904, 206, 600, 100));
	t_menuButtonQuit.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(604, 308, 600, 100));
	t_menuButtonNewGame.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(2, 206, 900, 100));
	t_menuButtonLoadGame.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(2, 104, 900, 100));
	t_menuButtonMultiplayer.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(904, 104, 900, 100));
	t_menuButtonReturn.loadFromFile("Data/Sprites/Buttons/menuButtons.png", IntRect(1206, 308, 600, 100));
	t_menuButtonLoad.loadFromFile("Data/Sprites/Buttons/load_button.png");
	t_menuButtonLoadThisGame.loadFromFile("Data/Sprites/Buttons/load_game_button.png");
	t_menuButtonDeleteThisGame.loadFromFile("Data/Sprites/Buttons/delete_game_button.png");
	t_menuButtonUp.loadFromFile("Data/Sprites/Buttons/button_up.png");
	t_menuButtonDown.loadFromFile("Data/Sprites/Buttons/button_down.png");
	t_menuButtonBlank.loadFromFile("Data/Sprites/Buttons/button_blank.png");

	t_newGameBackground.loadFromFile("Data/Sprites/NewGame/background_NewGame2.png");
	t_newGameButtonLeft.loadFromFile("Data/Sprites/NewGame/button_left.png");
	t_newGameButtonRight.loadFromFile("Data/Sprites/NewGame/button_right.png");
	t_newGameSmallWorld.loadFromFile("Data/Sprites/NewGame/small_world.png");
	t_newGameMediumWorld.loadFromFile("Data/Sprites/NewGame/medium_world.png");
	t_newGameBigWorld.loadFromFile("Data/Sprites/NewGame/big_world.png");
	t_newGameMiner.loadFromFile("Data/Sprites/NewGame/startClass_miner.png");
	t_newGameBuilder.loadFromFile("Data/Sprites/NewGame/startClass_builder.png");
	t_newGameWarrior.loadFromFile("Data/Sprites/NewGame/startClass_warrior.png");
	t_newGameMage.loadFromFile("Data/Sprites/NewGame/startClass_mage.png");

	t_pauseMenu.loadFromFile("Data/Sprites/pause_menu.png");
	t_pauseMenuContinueButton.loadFromFile("Data/Sprites/Buttons/continue_button.png");
	t_pauseMenuSaveButton.loadFromFile("Data/Sprites/Buttons/save_button.png");
	t_pauseMenuQuitButton.loadFromFile("Data/Sprites/Buttons/quit_button.png");

	t_BackgroundDead.loadFromFile("Data/Sprites/background_dead.png");

	t_gameBackground.loadFromFile("Data/Sprites/Background.png");
	t_gameNightSky.loadFromFile("Data/Sprites/nightsky.png");

	t_panelBeam.loadFromFile("Data/Sprites/Buttons/panel_beam.png");
	t_buttonInventory.loadFromFile("Data/Sprites/Buttons/button_inventory.png");
	t_buttonBuilding.loadFromFile("Data/Sprites/Buttons/button_building.png");
	t_buttonAttributes.loadFromFile("Data/Sprites/Buttons/button_attributes.png");
	t_buttonMagic.loadFromFile("Data/Sprites/Buttons/button_magic.png");

	t_inventoryWindow.loadFromFile("Data/Sprites/Inventory/InventoryNew.png");
	t_inventoryBeam.loadFromFile("Data/Sprites/Inventory/Inventory.png", IntRect(704, 2, 1000, 100));
	t_inventoryBeamFrame.loadFromFile("Data/Sprites/Inventory/Inventory.png", IntRect(1706, 2, 100, 100));

	t_equipmentWindow.loadFromFile("Data/Sprites/Inventory/Equipment.png");

	t_expBeam.loadFromFile("Data/Sprites/Panels/Exp_beam.png");
	t_expFrame.loadFromFile("Data/Sprites/Panels/Exp_frame.png");
	t_lifeFrame.loadFromFile("Data/Sprites/Panels/life_frame.png");
	t_lifeBeam.loadFromFile("Data/Sprites/Panels/life_beam.png");
	t_manaBeam.loadFromFile("Data/Sprites/Panels/mana_beam.png");

	t_buildingWindow.loadFromFile("Data/Sprites/Building/building_menu.png");
	t_buildButton.loadFromFile("Data/Sprites/Building/build_button.png");
	t_arrowUp.loadFromFile("Data/Sprites/Building/arrow_up.png");
	t_arrowDown.loadFromFile("Data/Sprites/Building/arrow_down.png");
	t_buildThingBackground.loadFromFile("Data/Sprites/Building/building_menu_background_things.png");

	t_skillPage.loadFromFile("Data/Sprites/Skills/character_info.png");
	t_levelUp.loadFromFile("Data/Sprites/Skills/levelUp.png");
	t_newSkillSpeed.loadFromFile("Data/Sprites/Skills/levelUp_speed.png");
	t_newSkillStrength.loadFromFile("Data/Sprites/Skills/levelUp_strength.png");
	t_newSkillHealth.loadFromFile("Data/Sprites/Skills/levelUp_health.png");
	t_newSkillBreakingSpeed.loadFromFile("Data/Sprites/Skills/levelUp_breakingSpeed.png");
	t_newSkillArmour.loadFromFile("Data/Sprites/Skills/levelUp_armour.png");
	t_newSkillLuck.loadFromFile("Data/Sprites/Skills/levelUp_luck.png");
	t_newSkillMana.loadFromFile("Data/Sprites/Skills/levelUp_mana.png");
	t_newSkillRecipe.loadFromFile("Data/Sprites/Skills/levelUp_recipe.png");

	t_furnanceMenu.loadFromFile("Data/Sprites/Inventory/furnance_menu2.png");

	t_buildingInfo_woodwall.loadFromFile("Data/Sprites/Building/building_info_woodwall.png");
	t_buildingInfo_stonewall.loadFromFile("Data/Sprites/Building/building_info_stonewall.png");
	t_buildingInfo_woodstaff.loadFromFile("Data/Sprites/Building/building_info_woodstaff.png");
	t_buildingInfo_pickaxe.loadFromFile("Data/Sprites/Building/building_info_pickaxe.png");
	t_buildingInfo_ladder.loadFromFile("Data/Sprites/Building/building_info_ladder.png");
	t_buildingInfo_furnance.loadFromFile("Data/Sprites/Building/building_info_furnance.png");
	t_buildingInfo_chest.loadFromFile("Data/Sprites/Building/building_info_chest.png");
	t_buildingInfo_cupboard.loadFromFile("Data/Sprites/Building/building_info_cupboard.png");
	t_buildingInfo_door.loadFromFile("Data/Sprites/Building/building_info_door.png");
	t_buildingInfo_glue.loadFromFile("Data/Sprites/Building/building_info_glue.png");
	t_buildingInfo_iron_helmet.loadFromFile("Data/Sprites/Building/building_info_iron_helmet.png");
	t_buildingInfo_iron_armour.loadFromFile("Data/Sprites/Building/building_info_iron_armour.png");
	t_buildingInfo_iron_trousers.loadFromFile("Data/Sprites/Building/building_info_iron_trousers.png");
	t_buildingInfo_iron_ring.loadFromFile("Data/Sprites/Building/building_info_iron_ring.png");
	t_buildingInfo_arcanus_ring.loadFromFile("Data/Sprites/Building/building_info_arcanus_ring.png");
    t_buildingInfo_table.loadFromFile("Data/Sprites/Building/building_info_table.png");
	t_buildingInfo_sword.loadFromFile("Data/Sprites/Building/building_info_sword.png");
	t_buildingInfo_lantern.loadFromFile("Data/Sprites/Building/building_info_lantern.png");
	t_buildingInfo_candle.loadFromFile("Data/Sprites/Building/building_info_candle.png");
	t_buildingInfo_marblewall.loadFromFile("Data/Sprites/Building/building_info_marble_wall.png");

	t_blockTextures_dirt.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(104, 2, 100, 100));
	t_blockTextures_stone.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(614, 2, 100, 100));
	t_blockTextures_wood.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(818, 2, 100, 100));
	t_blockTextures_coalBlock.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(2, 2, 100, 100));
	t_blockTextures_ironBlock.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(308, 2, 100, 100));
	t_blockTextures_goldBlock.loadFromFile("Data/Sprites/Objects/Blocks/gold_block.png");
	t_blockTextures_arcanusBlock.loadFromFile("Data/Sprites/Objects/Blocks/arcanus_block.png");
	t_blockTextures_stoneWall.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(716, 2, 100, 100));
	t_blockTextures_woodWall.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(920, 2, 100, 100));
	t_blockTextures_ladder.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(410, 2, 100, 100));
	t_blockTextures_noTexture.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(512, 2, 100, 100));
	t_blockTextures_furnance.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(206, 2, 100, 100));
	t_blockTextures_chest.loadFromFile("Data/Sprites/Objects/Blocks/chest.png", IntRect(0, 0, 100, 100));
	t_blockTextures_cupboard.loadFromFile("Data/Sprites/Objects/Blocks/cupboard.png");
	t_blockTextures_door.loadFromFile("Data/Sprites/Objects/Blocks/door.png");
	t_blockTextures_table.loadFromFile("Data/Sprites/Objects/Blocks/table.png");
	t_blockTextures_lantern.loadFromFile("Data/Sprites/Objects/Blocks/lantern.png");
	t_blockTextures_marble.loadFromFile("Data/Sprites/Objects/Blocks/marble.png");
	t_blockTextures_marblewall.loadFromFile("Data/Sprites/Objects/Blocks/marble_wall.png");

	t_blockInventoryTexture_dirt.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(200, 2, 97, 97));
	t_blockInventoryTexture_stone.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(992, 2, 97, 97));
	t_blockInventoryTexture_wood.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(1190, 2, 97, 97));
	t_blockInventoryTexture_coal.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(2, 2, 97, 97));
	t_blockInventoryTexture_iron.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(497, 2, 97, 97));
	t_blockInventoryTexture_ironOre.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(596, 2, 97, 97));
	t_blockInventoryTexture_coalBlock.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(101, 2, 97, 97));
	t_blockInventoryTexture_ironBlock.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(398, 2, 97, 97));
	t_blockInventoryTexture_gold.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/gold_inventory.png");
	t_blockInventoryTexture_goldBlock.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/gold_block_inventory.png");
	t_blockInventoryTexture_goldOre.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/gold_ore_inventory.png");
	t_blockInventoryTexture_ladder.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(695, 2, 97, 97));
	t_blockInventoryTexture_stoneWall.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(893, 2, 97, 97));
	t_blockInventoryTexture_woodWall.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(1289, 2, 97, 97));
	t_blockInventoryTexture_woodStaff.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(1091, 2, 97, 97));
	t_blockInventoryTexture_pickaxe.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(794, 2, 97, 97));
	t_blockInventoryTexture_furnance.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/inventory_sprites.png", IntRect(299, 2, 97, 97));
	t_blockInventoryTexture_chest.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/chest_inventory.png");
	t_blockInventoryTexture_cupboard.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/cupboard_inventory.png");
	t_blockInventoryTexture_door.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/door_inventory.png");
	t_blockInventoryTexture_glue.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/glue_inventory.png");
	t_blockInventoryTexture_iron_helmet.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/iron_helmet_inventory.png");
	t_blockInventoryTexture_iron_armour.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/iron_armour_inventory.png");
	t_blockInventoryTexture_iron_trousers.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/iron_trousers_inventory.png");
	t_blockInventoryTexture_iron_ring.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/iron_ring_inventory.png");
	t_blockInventoryTexture_arcanusBlock.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/arcanus_block_inventory.png");
	t_blockInventoryTexture_arcanusOre.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/arcanus_ore_inventory.png");
	t_blockInventoryTexture_arcanus_ring.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/arcanus_ring_inventory.png");
	t_blockInventoryTexture_slime.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/slime_inventory.png");
	t_blockInventoryTexture_recipe.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/recipe_inventory.png");
	t_blockInventoryTexture_table.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/table_inventory.png");
	t_blockInventoryTexture_very_rare_ring.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/very_rare_ring_inventory.png");
	t_blockInventoryTexture_magic_hat.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/magic_hat_inventory.png");
	t_blockInventoryTexture_sword.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/sword_inventory.png");
	t_blockInventoryTexture_lantern.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/lantern_inventory.png");
	t_blockInventoryTexture_candle.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/candle_inventory.png");
	t_blockInventoryTexture_wax.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/wax_inventory.png");
	t_blockInventoryTexture_marble.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/marble_inventory.png");
	t_blockInventoryTexture_marblewall.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/marble_wall_inventory.png");

	t_blockLittleTexture_dirt.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(86, 2, 40, 40));
	t_blockLittleTexture_stone.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(464, 2, 40, 40));
	t_blockLittleTexture_wood.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(548, 2, 40, 40));
	t_blockLittleTexture_coal.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(2, 2, 40, 40));
	t_blockLittleTexture_iron.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(212, 2, 40, 40));
	t_blockLittleTexture_ironOre.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(254, 2, 40, 40));
	t_blockLittleTexture_coalBlock.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(44, 2, 40, 40));
	t_blockLittleTexture_ironBlock.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(170, 2, 40, 40));
	t_blockLittleTexture_gold.loadFromFile("Data/Sprites/Objects/LittleItems/gold_little.png");
	t_blockLittleTexture_goldBlock.loadFromFile("Data/Sprites/Objects/LittleItems/gold_block_little.png");
	t_blockLittleTexture_goldOre.loadFromFile("Data/Sprites/Objects/LittleItems/gold_ore_little.png");
	t_blockLittleTexture_ladder.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(296, 2, 40, 40));
	t_blockLittleTexture_stoneWall.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(380, 2, 40, 40));
	t_blockLittleTexture_woodWall.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(590, 2, 40, 40));
	t_blockLittleTexture_woodStaff.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(506, 2, 40, 40));
	t_blockLittleTexture_pickaxe.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(338, 2, 40, 40));
	t_blockLittleTexture_furnance.loadFromFile("Data/Sprites/Objects/LittleItems/little_items.png", IntRect(128, 2, 40, 40));
	t_blockLittleTexture_chest.loadFromFile("Data/Sprites/Objects/LittleItems/chest_little.png");
	t_blockLittleTexture_cupboard.loadFromFile("Data/Sprites/Objects/LittleItems/cupboard_little.png");
	t_blockLittleTexture_door.loadFromFile("Data/Sprites/Objects/LittleItems/door_little.png");
	t_blockLittleTexture_glue.loadFromFile("Data/Sprites/Objects/LittleItems/glue_little.png");
	t_blockLittleTexture_iron_helmet.loadFromFile("Data/Sprites/Objects/LittleItems/iron_helmet_little.png");
	t_blockLittleTexture_iron_armour.loadFromFile("Data/Sprites/Objects/LittleItems/iron_armour_little.png");
	t_blockLittleTexture_iron_trousers.loadFromFile("Data/Sprites/Objects/LittleItems/iron_trousers_little.png");
	t_blockLittleTexture_iron_ring.loadFromFile("Data/Sprites/Objects/LittleItems/iron_ring_little.png");
	t_blockLittleTexture_arcanusBlock.loadFromFile("Data/Sprites/Objects/LittleItems/arcanus_block_little.png");
	t_blockLittleTexture_arcanusOre.loadFromFile("Data/Sprites/Objects/LittleItems/arcanus_ore_little.png");
	t_blockLittleTexture_arcanus_ring.loadFromFile("Data/Sprites/Objects/LittleItems/arcanus_ring_little.png");
	t_blockLittleTexture_slime.loadFromFile("Data/Sprites/Objects/LittleItems/slime_little.png");
	t_blockLittleTexture_recipe.loadFromFile("Data/Sprites/Objects/LittleItems/recipe_little.png");
	t_blockLittleTexture_table.loadFromFile("Data/Sprites/Objects/LittleItems/table_little.png");
	t_blockLittleTexture_very_rare_ring.loadFromFile("Data/Sprites/Objects/LittleItems/very_rare_ring_little.png");
	t_blockLittleTexture_magic_hat.loadFromFile("Data/Sprites/Objects/LittleItems/magic_hat_little.png");
	t_blockLittleTexture_sword.loadFromFile("Data/Sprites/Objects/LittleItems/sword_little.png");
	t_blockLittleTexture_lantern.loadFromFile("Data/Sprites/Objects/LittleItems/lantern_little.png");
	t_blockLittleTexture_candle.loadFromFile("Data/Sprites/Objects/LittleItems/candle_little.png");
	t_blockLittleTexture_wax.loadFromFile("Data/Sprites/Objects/LittleItems/wax_little.png");
	t_blockLittleTexture_marble.loadFromFile("Data/Sprites/Objects/LittleItems/marble_little.png");
	t_blockLittleTexture_marblewall.loadFromFile("Data/Sprites/Objects/LittleItems/marble_wall_little.png");

	t_tool_pickaxe.loadFromFile("Data/Sprites/Objects/Tools/Pickaxe_carried.png");
	t_tool_sword.loadFromFile("Data/Sprites/Objects/Tools/sword_carried.png");
	t_tool_lantern.loadFromFile("Data/Sprites/Objects/Tools/lantern_carried.png");

	t_equipment_iron_helmet.loadFromFile("Data/Sprites/Objects/Equipment/iron_helmet.png");
	t_equipment_iron_armour.loadFromFile("Data/Sprites/Objects/Equipment/iron_armour.png");
	t_equipment_iron_trousers.loadFromFile("Data/Sprites/Objects/Equipment/iron_trousers.png");
	t_equipment_magic_hat.loadFromFile("Data/Sprites/Objects/Equipment/magic_hat.png");
	t_equipment_candle.loadFromFile("Data/Sprites/Objects/Equipment/candle_helmet.png");

	t_breakingAnimation.loadFromFile("Data/Sprites/Objects/Blocks/breaking_animation.png");
	t_smoke.loadFromFile("Data/Sprites/Objects/Blocks/smoke2.png");

	t_dwarf_body.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(1008, 2, 106, 60));
	t_dwarf_legs.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(236, 2, 770, 50));
	t_dwarf_arm.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(2, 2, 232, 38));

	t_bee.loadFromFile("Data/Sprites/Living/bee.png");

	t_goblin_body.loadFromFile("Data/Sprites/Living/goblin_upper_body2.png");
	t_goblin_legs.loadFromFile("Data/Sprites/Living/goblin_legs2.png");
	t_goblin_arm.loadFromFile("Data/Sprites/Living/goblin_arm2.png");
	
	m_musicMenu.openFromFile("Data/Music/Music1.ogg");
	m_musicMenu.setLoop(true);
	m_musicGame[0].openFromFile("Data/Music/Music2.ogg");
	m_musicGame[1].openFromFile("Data/Music/Music3.ogg");
	m_musicGame[2].openFromFile("Data/Music/Music4.ogg");
	m_musicGame[3].openFromFile("Data/Music/Music5.ogg");
	m_musicGame[4].openFromFile("Data/Music/Music6.ogg");
	m_musicGame[5].openFromFile("Data/Music/Music7.ogg");
	m_musicGame[6].openFromFile("Data/Music/Music8.ogg");
	m_musicGame[7].openFromFile("Data/Music/Music9.ogg");
	m_musicGame[8].openFromFile("Data/Music/Music10.ogg");
	m_musicGame[9].openFromFile("Data/Music/Music11.ogg");

	for(int i = 0; i < 10; i++)
		m_musicGame[i].setVolume(50);

	m_goldSound[0].loadFromFile("Data/Sounds/gold1.ogg");
	m_goldSound[1].loadFromFile("Data/Sounds/gold2.ogg");
	m_goldSound[2].loadFromFile("Data/Sounds/gold3.ogg");
	
}
