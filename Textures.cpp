#include "Textures.hpp"






//loads all textures
void TextureLoading::LoadTextures()
{
	t_menuBackground.loadFromFile("Data/Sprites/Menu2.png");
	t_menuButtonPlay.loadFromFile("Data/Sprites/Buttons/play_button.png");
	t_menuButtonOptions.loadFromFile("Data/Sprites/Buttons/option_button.png");
	t_menuButtonHighscore.loadFromFile("Data/Sprites/Buttons/highscore_button.png");
	t_menuButtonQuit.loadFromFile("Data/Sprites/Buttons/quitButton.png");
	t_menuButtonDeleteHighscore.loadFromFile("Data/Sprites/Buttons/delete_highscore_button.png");
	t_menuButtonSaveHighscore.loadFromFile("Data/Sprites/Buttons/save_highscore_button.png");
	t_menuButtonNewGame.loadFromFile("Data/Sprites/Buttons/new_game_button2.png");
	t_menuButtonLoadGame.loadFromFile("Data/Sprites/Buttons/load_game_button2.png");
	t_menuButtonMultiplayer.loadFromFile("Data/Sprites/Buttons/Multiplayer_game_button_menu2.png");
	t_menuButtonReturn.loadFromFile("Data/Sprites/Buttons/return_button.png");
	t_menuButtonLoad.loadFromFile("Data/Sprites/Buttons/load_button2.png");
	t_menuButtonLoadThisGame.loadFromFile("Data/Sprites/Buttons/load_game_button.png");
	t_menuButtonDeleteThisGame.loadFromFile("Data/Sprites/Buttons/delete_game_button.png");
	t_menuButtonUp.loadFromFile("Data/Sprites/Buttons/button_up.png");
	t_menuButtonDown.loadFromFile("Data/Sprites/Buttons/button_down.png");
	t_menuButtonBlank.loadFromFile("Data/Sprites/Buttons/button_blank.png");
	t_optionsButton_beam_on.loadFromFile("Data/Sprites/Buttons/beamnumbers_on.png");
	t_optionsButton_beam_off.loadFromFile("Data/Sprites/Buttons/beamnumbers_off.png");
	t_optionsButton_inventory_on.loadFromFile("Data/Sprites/Buttons/button_option_inventorynumbers_on.png");
	t_optionsButton_inventory_off.loadFromFile("Data/Sprites/Buttons/button_option_inventorynumbers_off.png");

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
	t_gameNightSky.loadFromFile("Data/Sprites/nightsky3.png");

	t_panelBeam.loadFromFile("Data/Sprites/Buttons/panel_beam.png");
	t_buttonInventory.loadFromFile("Data/Sprites/Buttons/button_inventory.png");
	t_buttonBuilding.loadFromFile("Data/Sprites/Buttons/button_building.png");
	t_buttonAttributes.loadFromFile("Data/Sprites/Buttons/button_attributes.png");
	t_buttonMagic.loadFromFile("Data/Sprites/Buttons/button_magic.png");
	t_buttonClose.loadFromFile("Data/Sprites/Buttons/close_button.png");

	t_inventoryWindow.loadFromFile("Data/Sprites/Inventory/InventoryNew.png");
	t_inventoryBeam.loadFromFile("Data/Sprites/Inventory/Inventory.png", IntRect(704, 2, 1000, 100));
	t_inventoryBeamFrame.loadFromFile("Data/Sprites/Inventory/Inventory.png", IntRect(1706, 2, 100, 100));

	t_equipmentWindow.loadFromFile("Data/Sprites/Inventory/Equipment.png");

	t_cookingBookWindow.loadFromFile("Data/Sprites/Panels/cookingbook_menu.png");
	t_nextPageLeft.loadFromFile("Data/Sprites/Cooking/nextPageLeft_button.png");
	t_nextPageRight.loadFromFile("Data/Sprites/Cooking/nextPageRight_button.png");
	t_cookingMead.loadFromFile("Data/Sprites/Cooking/mead_recipe.png");
	t_cookingSlimepudding.loadFromFile("Data/Sprites/Cooking/slimepudding_recipe.png");
	t_cookingRadishsoup.loadFromFile("Data/Sprites/Cooking/radishsoup_recipe.png");
	t_cookingBread.loadFromFile("Data/Sprites/Cooking/bread_recipe.png");

	t_expBeam.loadFromFile("Data/Sprites/Panels/Exp_beam.png");
	t_expFrame.loadFromFile("Data/Sprites/Panels/Exp_frame.png");
	t_lifeFrame.loadFromFile("Data/Sprites/Panels/life_frame.png");
	t_lifeBeam.loadFromFile("Data/Sprites/Panels/life_beam.png");
	t_manaBeam.loadFromFile("Data/Sprites/Panels/mana_beam.png");

	t_status[0].loadFromFile("Data/Sprites/Effects/status_armour.png");
	t_status[1].loadFromFile("Data/Sprites/Effects/status_breaking_speed.png");
	t_status[2].loadFromFile("Data/Sprites/Effects/status_critical_chance.png");
	t_status[3].loadFromFile("Data/Sprites/Effects/status_critical_damage.png");
	t_status[4].loadFromFile("Data/Sprites/Effects/status_drunk.png");
	t_status[5].loadFromFile("Data/Sprites/Effects/status_healthregeneration.png");
	t_status[6].loadFromFile("Data/Sprites/Effects/status_luck.png");
	t_status[7].loadFromFile("Data/Sprites/Effects/status_manaregeneration.png");
	t_status[8].loadFromFile("Data/Sprites/Effects/status_speed.png");
	t_status[9].loadFromFile("Data/Sprites/Effects/status_strength.png");

	t_buildingWindow.loadFromFile("Data/Sprites/Building/building_menu.png");
	t_buildButton.loadFromFile("Data/Sprites/Building/build_button.png");
	t_arrowUp.loadFromFile("Data/Sprites/Building/arrow_up.png");
	t_arrowDown.loadFromFile("Data/Sprites/Building/arrow_down.png");
	t_buildThingBackground.loadFromFile("Data/Sprites/Building/building_menu_background_things.png");

	t_skillPage.loadFromFile("Data/Sprites/Skills/character_info2.png");
	t_levelUp.loadFromFile("Data/Sprites/Skills/levelUp.png");
	t_levelUp_button.loadFromFile("Data/Sprites/Skills/levelUp_button.png");
	t_newSkillSpeed.loadFromFile("Data/Sprites/Skills/levelUp_speed.png");
	t_newSkillStrength.loadFromFile("Data/Sprites/Skills/levelUp_strength.png");
	t_newSkillHealth.loadFromFile("Data/Sprites/Skills/levelUp_health.png");
	t_newSkillBreakingSpeed.loadFromFile("Data/Sprites/Skills/levelUp_breakingSpeed.png");
	t_newSkillArmour.loadFromFile("Data/Sprites/Skills/levelUp_armour.png");
	t_newSkillLuck.loadFromFile("Data/Sprites/Skills/levelUp_luck.png");
	t_newSkillMana.loadFromFile("Data/Sprites/Skills/levelUp_mana.png");
	t_newSkillHealthRegeneration.loadFromFile("Data/Sprites/Skills/levelUp_healthRegeneration.png");
	t_newSkillManaRegeneration.loadFromFile("Data/Sprites/Skills/levelUp_manaRegeneration.png");
	t_newSkillCriticalChance.loadFromFile("Data/Sprites/Skills/levelUp_criticalChance.png");
	t_newSkillCriticalDamage.loadFromFile("Data/Sprites/Skills/levelUp_criticalDamage.png");
	t_newSkillMagicPoints.loadFromFile("Data/Sprites/Skills/levelUp_magicPoints.png");
	t_newSkillRecipe.loadFromFile("Data/Sprites/Skills/levelUp_recipe.png");

	t_furnanceMenu.loadFromFile("Data/Sprites/Inventory/furnance_menu2.png");
	t_cauldronMenu.loadFromFile("Data/Sprites/Inventory/cooking_menu.png");
	t_cookingButton.loadFromFile("Data/Sprites/Buttons/cooking_button.png");

	t_magicMenu.loadFromFile("Data/Sprites/Magic/magic_menu.png");
	t_buttonPlus.loadFromFile("Data/Sprites/Magic/plus.png");
	t_spell[0].loadFromFile("Data/Sprites/Magic/spell_fireball.png");
	t_spell[1].loadFromFile("Data/Sprites/Magic/spell_heal.png");
	t_spell[2].loadFromFile("Data/Sprites/Magic/spell_ice.png");
	t_spell[3].loadFromFile("Data/Sprites/Magic/spell_alchemy.png");
	t_spell[4].loadFromFile("Data/Sprites/Magic/spell_light.png");
	t_spell[5].loadFromFile("Data/Sprites/Magic/spell_manashield.png");
	t_fireballLeft.loadFromFile("Data/Sprites/Magic/fireball.png", IntRect(80, 0, 80, 30));
	t_fireballRight.loadFromFile("Data/Sprites/Magic/fireball.png", IntRect(0, 0, 80, 30));
	t_explosion.loadFromFile("Data/Sprites/Magic/explosion.png");
	t_healing.loadFromFile("Data/Sprites/Magic/heal_animation.png");
	t_manashield.loadFromFile("Data/Sprites/Magic/manashield.png");
	t_alchemy.loadFromFile("Data/Sprites/Magic/alchemy.png");
	t_lightsphere.loadFromFile("Data/Sprites/Magic/light.png");
	t_rubbishAnimation.loadFromFile("Data/Sprites/Objects/Blocks/rubbish_animation.png");
	t_dynamiteAnimation.loadFromFile("Data/Sprites/Magic/dynamite_effect.png");
	t_iceballLeft.loadFromFile("Data/Sprites/Magic/iceball.png", IntRect(80, 0, 80, 30));
	t_iceballRight.loadFromFile("Data/Sprites/Magic/iceball.png", IntRect(0, 0, 80, 30));
	t_ice_goblin.loadFromFile("Data/Sprites/Magic/ice_goblin.png");
	t_ice_bee.loadFromFile("Data/Sprites/Magic/ice_bee.png");
	t_ice_ogre.loadFromFile("Data/Sprites/Magic/ice_ogre.png");

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
	t_buildingInfo_beehouse.loadFromFile("Data/Sprites/Building/building_info_bee_house.png");
	t_buildingInfo_torch.loadFromFile("Data/Sprites/Building/building_info_torch.png");
	t_buildingInfo_cauldron.loadFromFile("Data/Sprites/Building/building_info_cauldron.png");
	t_buildingInfo_battleaxe.loadFromFile("Data/Sprites/Building/building_info_battleaxe.png");
	t_buildingInfo_sawdust.loadFromFile("Data/Sprites/Building/building_info_sawdust.png");
	t_buildingInfo_battlestone.loadFromFile("Data/Sprites/Building/building_info_battlestone.png");
	t_buildingInfo_diadochitarmour.loadFromFile("Data/Sprites/Building/building_info_diadochit_armour.png");
	t_buildingInfo_bricks.loadFromFile("Data/Sprites/Building/building_info_bricks.png");
	t_buildingInfo_brickwall.loadFromFile("Data/Sprites/Building/building_info_brickwall.png");

	t_blockTextures_dirt.loadFromFile("Data/Sprites/Objects/Blocks/dirt.png");
	t_blockTextures_stone.loadFromFile("Data/Sprites/Objects/Blocks/stone.png");
	t_blockTextures_wood.loadFromFile("Data/Sprites/Objects/Blocks/blocks_texture.png", IntRect(818, 2, 100, 100));
	t_blockTextures_coalBlock.loadFromFile("Data/Sprites/Objects/Blocks/coal_block.png");
	t_blockTextures_ironBlock.loadFromFile("Data/Sprites/Objects/Blocks/iron_block.png");
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
	t_blockTextures_treetrunk.loadFromFile("Data/Sprites/Objects/Blocks/tree_trunk.png");
	t_blockTextures_treecrown.loadFromFile("Data/Sprites/Objects/Blocks/tree_crown.png");
	t_blockTextures_marblewall.loadFromFile("Data/Sprites/Objects/Blocks/marble_wall.png");
	t_blockTextures_beehouse.loadFromFile("Data/Sprites/Objects/Blocks/bee_house.png");
	t_blockTextures_beehive_left.loadFromFile("Data/Sprites/Objects/Blocks/beehive.png", IntRect(0,0,117,100));
	t_blockTextures_beehive_right.loadFromFile("Data/Sprites/Objects/Blocks/beehive.png", IntRect(117, 0, 117, 100));
	t_blockTextures_torch_ground.loadFromFile("Data/Sprites/Objects/Blocks/torch.png", IntRect(0, 0, 100, 100));
	t_blockTextures_torch_wall.loadFromFile("Data/Sprites/Objects/Blocks/torch.png", IntRect(100, 0, 100, 100));
	t_blockTextures_torch_left.loadFromFile("Data/Sprites/Objects/Blocks/torch.png", IntRect(300, 0, 100, 100));
	t_blockTextures_torch_right.loadFromFile("Data/Sprites/Objects/Blocks/torch.png", IntRect(200, 0, 100, 100));
	t_blockTextures_cauldron.loadFromFile("Data/Sprites/Objects/Blocks/cauldron.png");
	t_blockTextures_clover.loadFromFile("Data/Sprites/Objects/Blocks/cloverleaf.png");
	t_blockTextures_radish.loadFromFile("Data/Sprites/Objects/Blocks/radish.png");
	t_blockTextures_mushroom.loadFromFile("Data/Sprites/Objects/Blocks/mushroom.png");
	t_blockTextures_bedrock.loadFromFile("Data/Sprites/Objects/Blocks/bedrock.png");
	t_blockTextures_stalagtit1.loadFromFile("Data/Sprites/Objects/Blocks/stalagmit_2.png");
	t_blockTextures_stalagtit2.loadFromFile("Data/Sprites/Objects/Blocks/stalagmit_3.png");
	t_blockTextures_stalagtit3.loadFromFile("Data/Sprites/Objects/Blocks/stalagmit_4.png");
	t_blockTextures_stalagtit4.loadFromFile("Data/Sprites/Objects/Blocks/stalagmit_5.png");
	t_blockTextures_rubbish.loadFromFile("Data/Sprites/Objects/Blocks/rubbish_pile.png");
	t_blockTextures_bricks.loadFromFile("Data/Sprites/Objects/Blocks/bricks.png");
	t_blockTextures_brickwall.loadFromFile("Data/Sprites/Objects/Blocks/dark_brick_wall.png");
	t_blockTextures_princessCage.loadFromFile("Data/Sprites/Objects/Blocks/princess_in_cage.png");
	t_blockTextures_princessCage2.loadFromFile("Data/Sprites/Objects/Blocks/princess_in_cage2.png");

	t_dirtRimTop.loadFromFile("Data/Sprites/Objects/Blocks/dirt_rim_top.png");
	t_dirtRimBottom.loadFromFile("Data/Sprites/Objects/Blocks/dirt_rim_bottom.png");
	t_dirtRimLeft.loadFromFile("Data/Sprites/Objects/Blocks/dirt_rim_left.png");
	t_dirtRimRight.loadFromFile("Data/Sprites/Objects/Blocks/dirt_rim_right.png");
	t_stoneRimTop.loadFromFile("Data/Sprites/Objects/Blocks/stone_rim_top.png");
	t_stoneRimBottom.loadFromFile("Data/Sprites/Objects/Blocks/stone_rim_bottom.png");
	t_stoneRimLeft.loadFromFile("Data/Sprites/Objects/Blocks/stone_rim_left.png");
	t_stoneRimRight.loadFromFile("Data/Sprites/Objects/Blocks/stone_rim_right.png");
	t_treeRim.loadFromFile("Data/Sprites/Objects/Blocks/tree_rim.png");

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
	t_blockInventoryTexture_treetrunk.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/tree_trunk_inventory.png");
	t_blockInventoryTexture_treecrown.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/tree_crown_inventory.png");
	t_blockInventoryTexture_beehive.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/beehive_inventory.png");
	t_blockInventoryTexture_beehouse.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/bee_house_inventory.png");
	t_blockInventoryTexture_honey.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/honey_inventory.png");
	t_blockInventoryTexture_torch.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/torch_inventory.png");
	t_blockInventoryTexture_cauldron.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/cauldron_inventory.png");
	t_blockInventoryTexture_mead.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/mead_inventory.png");
	t_blockInventoryTexture_slimepudding.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/slime_pudding_inventory.png");
	t_blockInventoryTexture_clover.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/cloverleaf_inventory.png");
	t_blockInventoryTexture_battleaxe.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/battleaxe_inventory.png");
	t_blockInventoryTexture_radish.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/radish_inventory.png");
	t_blockInventoryTexture_radishsoup.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/radish_soup_inventory.png");
	t_blockInventoryTexture_cookingbook.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/cookingbook_inventory.png");
	t_blockInventoryTexture_bread.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/bread_inventory.png");
	t_blockInventoryTexture_sawdust.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/sawdust_inventory.png");
	t_blockInventoryTexture_mushroom.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/mushroom_inventory.png");
	t_blockInventoryTexture_diadochit.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/diadochit_inventory.png");
	t_blockInventoryTexture_battlestone.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/battlestone_inventory.png");
	t_blockInventoryTexture_diadochitarmour.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/diadochit_armour_inventory.png");
	t_blockInventoryTexture_bedrock.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/bedrock_inventory.png");
	t_blockInventoryTexture_bricks.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/bricks_inventory.png");
	t_blockInventoryTexture_brickwall.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/dark_brick_wall_inventory.png");
	t_blockInventoryTexture_dynamite.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/dynamite_inventory.png");
	t_blockInventoryTexture_key.loadFromFile("Data/Sprites/Inventory/Inventory_pictures/key_inventory.png");
	t_spellInventoryTexture_fireball.loadFromFile("Data/Sprites/Magic/spell_fireball.png", IntRect(0, 0, 97, 97));
	t_spellInventoryTexture_heal.loadFromFile("Data/Sprites/Magic/spell_heal.png", IntRect(0, 0, 97, 97));
	t_spellInventoryTexture_ice.loadFromFile("Data/Sprites/Magic/spell_ice.png", IntRect(0, 0, 97, 97));
	t_spellInventoryTexture_alchemy.loadFromFile("Data/Sprites/Magic/spell_alchemy.png", IntRect(0, 0, 97, 97));
	t_spellInventoryTexture_light.loadFromFile("Data/Sprites/Magic/spell_light.png", IntRect(0, 0, 97, 97));
	t_spellInventoryTexture_manashield.loadFromFile("Data/Sprites/Magic/spell_manashield.png", IntRect(0, 0, 97, 97));

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
	t_blockLittleTexture_beehive.loadFromFile("Data/Sprites/Objects/LittleItems/beehive_little.png");
	t_blockLittleTexture_beehouse.loadFromFile("Data/Sprites/Objects/LittleItems/bee_house_little.png");
	t_blockLittleTexture_honey.loadFromFile("Data/Sprites/Objects/LittleItems/honey_little.png");
	t_blockLittleTexture_torch.loadFromFile("Data/Sprites/Objects/LittleItems/torch_little.png");
	t_blockLittleTexture_cauldron.loadFromFile("Data/Sprites/Objects/LittleItems/cauldron_little.png");
	t_blockLittleTexture_mead.loadFromFile("Data/Sprites/Objects/LittleItems/mead_little.png");
	t_blockLittleTexture_slimepudding.loadFromFile("Data/Sprites/Objects/LittleItems/slime_pudding_little.png");
	t_blockLittleTexture_clover.loadFromFile("Data/Sprites/Objects/LittleItems/cloverleaf_little.png");
	t_blockLittleTexture_battleaxe.loadFromFile("Data/Sprites/Objects/LittleItems/battleaxe_little.png");
	t_blockLittleTexture_radish.loadFromFile("Data/Sprites/Objects/LittleItems/radish_little.png");
	t_blockLittleTexture_radishsoup.loadFromFile("Data/Sprites/Objects/LittleItems/radish_soup_little.png");
	t_blockLittleTexture_cookingbook.loadFromFile("Data/Sprites/Objects/LittleItems/cookingbook_little.png");
	t_blockLittleTexture_bread.loadFromFile("Data/Sprites/Objects/LittleItems/bread_little.png");
	t_blockLittleTexture_sawdust.loadFromFile("Data/Sprites/Objects/LittleItems/sawdust_little.png");
	t_blockLittleTexture_mushroom.loadFromFile("Data/Sprites/Objects/LittleItems/mushroom_little.png");
	t_blockLittleTexture_diadochit.loadFromFile("Data/Sprites/Objects/LittleItems/diadochit_little.png");
	t_blockLittleTexture_battlestone.loadFromFile("Data/Sprites/Objects/LittleItems/battlestone_little.png");
	t_blockLittleTexture_diadochitarmour.loadFromFile("Data/Sprites/Objects/LittleItems/diadochit_armour_little.png");
	t_blockLittleTexture_bedrock.loadFromFile("Data/Sprites/Objects/LittleItems/bedrock_little.png");
	t_blockLittleTexture_bricks.loadFromFile("Data/Sprites/Objects/LittleItems/bricks_little.png");
	t_blockLittleTexture_brickwall.loadFromFile("Data/Sprites/Objects/LittleItems/dark_brick_wall_little.png");
	t_blockLittleTexture_dynamite.loadFromFile("Data/Sprites/Objects/LittleItems/dynamite_little.png");
	t_blockLittleTexture_key.loadFromFile("Data/Sprites/Objects/LittleItems/key_little.png");


	t_tool_pickaxe.loadFromFile("Data/Sprites/Objects/Tools/Pickaxe_carried.png");
	t_tool_sword.loadFromFile("Data/Sprites/Objects/Tools/sword_carried.png");
	t_tool_lantern.loadFromFile("Data/Sprites/Objects/Tools/lantern_carried.png");
	t_tool_battleaxe.loadFromFile("Data/Sprites/Objects/Tools/battleaxe_carried.png");
	t_tool_battlestone.loadFromFile("Data/Sprites/Objects/Tools/battlestone_carried.png");
	t_tool_dynamite.loadFromFile("Data/Sprites/Objects/Tools/dynamite.png");

	t_equipment_iron_helmet.loadFromFile("Data/Sprites/Objects/Equipment/iron_helmet.png");
	t_equipment_iron_armour.loadFromFile("Data/Sprites/Objects/Equipment/iron_armour.png");
	t_equipment_iron_trousers.loadFromFile("Data/Sprites/Objects/Equipment/iron_trousers.png");
	t_equipment_magic_hat.loadFromFile("Data/Sprites/Objects/Equipment/magic_hat.png");
	t_equipment_candle.loadFromFile("Data/Sprites/Objects/Equipment/candle_helmet.png");
	t_equipment_diadochitarmour.loadFromFile("Data/Sprites/Objects/Equipment/diadochit_armour.png");

	t_breakingAnimation.loadFromFile("Data/Sprites/Objects/Blocks/breaking_animation.png");
	t_smoke.loadFromFile("Data/Sprites/Objects/Blocks/smoke2.png");

	t_dwarf_body.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(1008, 2, 106, 60));
	t_dwarf_legs.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(236, 2, 770, 50));
	t_dwarf_arm.loadFromFile("Data/Sprites/Living/Dwarf_animated.png", IntRect(2, 2, 232, 38));

	t_bee.loadFromFile("Data/Sprites/Living/bee.png");

	t_goblin_body.loadFromFile("Data/Sprites/Living/goblin_upper_body2.png");
	t_goblin_legs.loadFromFile("Data/Sprites/Living/goblin_legs2.png");
	t_goblin_legs2.loadFromFile("Data/Sprites/Living/goblin_legs3.png");
	t_goblin_arm.loadFromFile("Data/Sprites/Living/goblin_arm2.png");
	t_goblin_body2.loadFromFile("Data/Sprites/Living/goblin_upper_body3.png");
	t_goblin_arm2.loadFromFile("Data/Sprites/Living/goblin_arm3.png");
	t_goblin_body3.loadFromFile("Data/Sprites/Living/goblin_upper_body4.png");
	t_goblin_arm3.loadFromFile("Data/Sprites/Living/goblin_arm4.png");
	t_goblin_body_chest.loadFromFile("Data/Sprites/Living/goblin_upper_body_chest.png");
	t_goblin_body4.loadFromFile("Data/Sprites/Living/goblin_upper_body5.png");
	t_goblin_arm4.loadFromFile("Data/Sprites/Living/goblin_arm5.png");
	t_goblin_legs3.loadFromFile("Data/Sprites/Living/goblin_legs4.png");

	t_ogre_body.loadFromFile("Data/Sprites/Living/ogre_body.png");
	t_ogre_arm.loadFromFile("Data/Sprites/Living/ogre_arm_animated.png");
	t_ogre_legs.loadFromFile("Data/Sprites/Living/ogre_legs.png");
	t_ground_hit.loadFromFile("Data/Sprites/Living/ground_hit.png");

	s_drunkShader.loadFromFile("Data/Shaders/blur.frag", Shader::Fragment);

	f_coolsville.loadFromFile("Data/Fonts/coolsville.ttf");
	f_ltromatic.loadFromFile("Data/Fonts/ltromatic.ttf");
	f_cents18.loadFromFile("Data/Fonts/18cents.ttf");
}
