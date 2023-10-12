#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"
#include "Helpers.h"
#include "includes\ini.h"

#include "FEPlayerCarDB.h"
#include "QuickRaceUnlocker.h"
#include "UnlockSystem.h"
#include "UIQRCarSelect.h"

void LoadCarConfigs()
{
	CarConfig ACarConfig;
	std::vector<CarConfig> CarConfigs_temp;

	auto GeneralINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_General.ini";
	mINI::INIFile GeneralINIFile(GeneralINIPath.string());
	mINI::INIStructure GeneralINI;
	GeneralINIFile.read(GeneralINI);

	char CarININame[MAX_PATH];

	// Read default car config first
	DefaultCarConfig.CarTypeInfo = (DWORD*)((*(DWORD*)CarTypeInfoArray) + ReplacementCar * SingleCarTypeInfoBlockSize);

	// Main
	DefaultCarConfig.Main.ForceLODA = mINI_ReadInteger(GeneralINI, "Main", "ForceLODA", 0) != 0;
	DefaultCarConfig.Main.InitiallyUnlocked = mINI_ReadInteger(GeneralINI, "Main", "InitiallyUnlocked", -1);
	DefaultCarConfig.Main.EngineType = mINI_ReadInteger(GeneralINI, "Main", "EngineType", -1);
	DefaultCarConfig.Main.ScaleBrakesWithRims = mINI_ReadInteger(GeneralINI, "Main", "ScaleBrakesWithRims", 1);
	DefaultCarConfig.Main.ListAttachmentsUnderParts = mINI_ReadInteger(GeneralINI, "Main", "ListAttachmentsUnderParts", 1);

	// Category (also check Main for backwards compatibility)
	DefaultCarConfig.Category.Parts = mINI_ReadInteger(GeneralINI, "Main", "Parts", 1) != 0;
	DefaultCarConfig.Category.Performance = mINI_ReadInteger(GeneralINI, "Main", "Performance", 1) != 0;
	DefaultCarConfig.Category.Visual = mINI_ReadInteger(GeneralINI, "Main", "Visual", 1) != 0;

	DefaultCarConfig.Category.Parts = mINI_ReadInteger(GeneralINI, "Category", "Parts", DefaultCarConfig.Category.Parts) != 0;
	DefaultCarConfig.Category.Performance = mINI_ReadInteger(GeneralINI, "Category", "Performance", DefaultCarConfig.Category.Performance) != 0;
	DefaultCarConfig.Category.Visual = mINI_ReadInteger(GeneralINI, "Category", "Visual", DefaultCarConfig.Category.Visual) != 0;

	// Textures
	DefaultCarConfig.Textures.HeadlightOff = mINI_ReadInteger(GeneralINI, "Textures", "HeadlightOff", 0) != 0;
	DefaultCarConfig.Textures.DamageLights = mINI_ReadInteger(GeneralINI, "Textures", "DamageLights", 0) != 0;
	DefaultCarConfig.Textures.CentreBrake = mINI_ReadInteger(GeneralINI, "Textures", "CentreBrake", 0) != 0;
	DefaultCarConfig.Textures.Reverse = mINI_ReadInteger(GeneralINI, "Textures", "Reverse", 0) != 0;
	DefaultCarConfig.Textures.BrakelightOnfInGame = mINI_ReadInteger(GeneralINI, "Textures", "BrakelightOnfInGame", 0) != 0;
	DefaultCarConfig.Textures.TireInnerMask = mINI_ReadInteger(GeneralINI, "Textures", "TireInnerMask", 0) != 0;

	// Parts
	DefaultCarConfig.Parts.BodyKits = mINI_ReadInteger(GeneralINI, "Parts", "BodyKits", 1) != 0;
	DefaultCarConfig.Parts.Spoilers = mINI_ReadInteger(GeneralINI, "Parts", "Spoilers", 1) != 0;
	DefaultCarConfig.Parts.Rims = mINI_ReadInteger(GeneralINI, "Parts", "Rims", 1) != 0;
	DefaultCarConfig.Parts.RimsCustom = mINI_ReadInteger(GeneralINI, "Parts", "RimsCustom", 0) != 0;
	DefaultCarConfig.Parts.Hoods = mINI_ReadInteger(GeneralINI, "Parts", "Hoods", 1) != 0;
	DefaultCarConfig.Parts.RoofScoops = mINI_ReadInteger(GeneralINI, "Parts", "RoofScoops", 1) != 0;
	DefaultCarConfig.Parts.Interior = mINI_ReadInteger(GeneralINI, "Parts", "Interior", 0) != 0;
	DefaultCarConfig.Parts.Roof = mINI_ReadInteger(GeneralINI, "Parts", "Roof", 0) != 0;
	DefaultCarConfig.Parts.Brakes = mINI_ReadInteger(GeneralINI, "Parts", "Brakes", 0) != 0;
	DefaultCarConfig.Parts.Headlights = mINI_ReadInteger(GeneralINI, "Parts", "Headlights", 0) != 0;
	DefaultCarConfig.Parts.Taillights = mINI_ReadInteger(GeneralINI, "Parts", "Taillights", 0) != 0;
	DefaultCarConfig.Parts.Mirrors = mINI_ReadInteger(GeneralINI, "Parts", "Mirrors", 0) != 0;
	DefaultCarConfig.Parts.Attachments = mINI_ReadInteger(GeneralINI, "Parts", "Attachments", 0) % 11;

	// Performance
	DefaultCarConfig.Performance.Engine = mINI_ReadInteger(GeneralINI, "Performance", "Engine", 1) != 0;
	DefaultCarConfig.Performance.Transmission = mINI_ReadInteger(GeneralINI, "Performance", "Transmission", 1) != 0;
	DefaultCarConfig.Performance.Chassis = mINI_ReadInteger(GeneralINI, "Performance", "Chassis", 1) != 0;
	DefaultCarConfig.Performance.Nitrous = mINI_ReadInteger(GeneralINI, "Performance", "Nitrous", 1) != 0;
	DefaultCarConfig.Performance.Tires = mINI_ReadInteger(GeneralINI, "Performance", "Tires", 1) != 0;
	DefaultCarConfig.Performance.Brakes = mINI_ReadInteger(GeneralINI, "Performance", "Brakes", 1) != 0;
	DefaultCarConfig.Performance.Induction = mINI_ReadInteger(GeneralINI, "Performance", "Induction", 1) != 0;

	// Visual
	DefaultCarConfig.Visual.Paint = mINI_ReadInteger(GeneralINI, "Visual", "Paint", 1) != 0;
	DefaultCarConfig.Visual.PaintCustom = mINI_ReadInteger(GeneralINI, "Visual", "PaintCustom", 0) != 0;
	DefaultCarConfig.Visual.Vinyls = mINI_ReadInteger(GeneralINI, "Visual", "Vinyls", 1) != 0;
	DefaultCarConfig.Visual.VinylsCustom = mINI_ReadInteger(GeneralINI, "Visual", "VinylsCustom", 0) != 0;
	DefaultCarConfig.Visual.RimPaint = mINI_ReadInteger(GeneralINI, "Visual", "RimPaint", 1) != 0;
	DefaultCarConfig.Visual.WindowTint = mINI_ReadInteger(GeneralINI, "Visual", "WindowTint", 1) != 0;
	DefaultCarConfig.Visual.Decals = mINI_ReadInteger(GeneralINI, "Visual", "Decals", 1) != 0;
	DefaultCarConfig.Visual.DecalsWindshield = mINI_ReadInteger(GeneralINI, "Visual", "DecalsWindshield", 1) != 0;
	DefaultCarConfig.Visual.DecalsRearWindow = mINI_ReadInteger(GeneralINI, "Visual", "DecalsRearWindow", 1) != 0;
	DefaultCarConfig.Visual.DecalsLeftDoor = mINI_ReadInteger(GeneralINI, "Visual", "DecalsLeftDoor", 1) != 0;
	DefaultCarConfig.Visual.DecalsRightDoor = mINI_ReadInteger(GeneralINI, "Visual", "DecalsRightDoor", 1) != 0;
	DefaultCarConfig.Visual.DecalsLeftQuarter = mINI_ReadInteger(GeneralINI, "Visual", "DecalsLeftQuarter", 1) != 0;
	DefaultCarConfig.Visual.DecalsRightQuarter = mINI_ReadInteger(GeneralINI, "Visual", "DecalsRightQuarter", 1) != 0;
	DefaultCarConfig.Visual.Numbers = mINI_ReadInteger(GeneralINI, "Visual", "Numbers", 1) != 0;
	DefaultCarConfig.Visual.CustomGauges = mINI_ReadInteger(GeneralINI, "Visual", "CustomGauges", 1) != 0;
	DefaultCarConfig.Visual.Driver = mINI_ReadInteger(GeneralINI, "Visual", "Driver", 0) != 0;
	DefaultCarConfig.Visual.LicensePlate = mINI_ReadInteger(GeneralINI, "Visual", "LicensePlate", 0) != 0;
	DefaultCarConfig.Visual.Tires = mINI_ReadInteger(GeneralINI, "Visual", "Tires", 1) != 0;
	DefaultCarConfig.Visual.Neon = mINI_ReadInteger(GeneralINI, "Visual", "Neon", 1) != 0;

	// Icons
	DefaultCarConfig.Icons.Parts = mINI_ReadHashS(GeneralINI, "Icons", "Parts", "BROWSER_PARTS");
	DefaultCarConfig.Icons.PartsBodyKits = mINI_ReadHashS(GeneralINI, "Icons", "PartsBodyKits", "VISUAL_PART_BODY");
	DefaultCarConfig.Icons.PartsSpoilers = mINI_ReadHashS(GeneralINI, "Icons", "PartsSpoilers", "VISUAL_PART_SPOILER");
	DefaultCarConfig.Icons.PartsSpoilersCF = mINI_ReadHashS(GeneralINI, "Icons", "PartsSpoilersCF", "VISUAL_PART_SPOILER_CARBON");
	DefaultCarConfig.Icons.PartsRims = mINI_ReadHashS(GeneralINI, "Icons", "PartsRims", "VISUAL_PART_RIMS");
	DefaultCarConfig.Icons.PartsRimsCustom = mINI_ReadHashS(GeneralINI, "Icons", "PartsRimsCustom", "");
	DefaultCarConfig.Icons.PartsHoods = mINI_ReadHashS(GeneralINI, "Icons", "PartsHoods", "VISUAL_PART_HOOD");
	DefaultCarConfig.Icons.PartsHoodsCF = mINI_ReadHashS(GeneralINI, "Icons", "PartsHoodsCF", "VISUAL_PART_HOOD_CARBON");
	DefaultCarConfig.Icons.PartsRoofScoops = mINI_ReadHashS(GeneralINI, "Icons", "PartsRoofScoops", "VISUAL_PART_ROOF_SCOOP");
	DefaultCarConfig.Icons.PartsRoofScoopsCF = mINI_ReadHashS(GeneralINI, "Icons", "PartsRoofScoopsCF", "VISUAL_PART_ROOF_SCOOP_CARBON");
	DefaultCarConfig.Icons.PartsInterior = mINI_ReadHashS(GeneralINI, "Icons", "PartsInterior", "VISUAL_PART_INTERIOR");
	DefaultCarConfig.Icons.PartsRoof = mINI_ReadHashS(GeneralINI, "Icons", "PartsRoof", "VISUAL_PART_ROOF");
	DefaultCarConfig.Icons.PartsBrakes = mINI_ReadHashS(GeneralINI, "Icons", "PartsBrakes", "VISUAL_PART_BRAKE");
	DefaultCarConfig.Icons.PartsHeadlights = mINI_ReadHashS(GeneralINI, "Icons", "PartsHeadlights", "VISUAL_PART_HEAD_LIGHTS");
	DefaultCarConfig.Icons.PartsTaillights = mINI_ReadHashS(GeneralINI, "Icons", "PartsTaillights", "VISUAL_PART_TAIL_LIGHTS");
	DefaultCarConfig.Icons.PartsMirrors = mINI_ReadHashS(GeneralINI, "Icons", "PartsMirrors", "VISUAL_PART_SIDE_MIRROR");
	DefaultCarConfig.Icons.PartsAttachments = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachments", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment0 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment0", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment1 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment1", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment2 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment2", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment3 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment3", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment4 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment4", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment5 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment5", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment6 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment6", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment7 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment7", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment8 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment8", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.PartsAttachment9 = mINI_ReadHashS(GeneralINI, "Icons", "PartsAttachment9", "VISUAL_PART_ATTACHMENT");
	DefaultCarConfig.Icons.Performance = mINI_ReadHashS(GeneralINI, "Icons", "Performance", "BROWSER_PERFORMANCE");
	DefaultCarConfig.Icons.PerformanceEngine = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngine", "PERFORMANCE_ENGINE");
	DefaultCarConfig.Icons.PerformanceTransmission = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmission", "PERFORMANCE_TRANSMISSION");
	DefaultCarConfig.Icons.PerformanceChassis = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassis", "PERFORMANCE_SUSPENSION");
	DefaultCarConfig.Icons.PerformanceNitrous = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrous", "PERFORMANCE_NITROUS");
	DefaultCarConfig.Icons.PerformanceTires = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTires", "PERFORMANCE_TIRES");
	DefaultCarConfig.Icons.PerformanceBrakes = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakes", "PERFORMANCE_BRAKES");
	DefaultCarConfig.Icons.PerformanceTurbo = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurbo", "PERFORMANCE_TURBO");
	DefaultCarConfig.Icons.PerformanceSupercharger = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSupercharger", "PERFORMANCE_SUPERCHARGER");
	DefaultCarConfig.Icons.Visual = mINI_ReadHashS(GeneralINI, "Icons", "Visual", "BROWSER_VISUAL");
	DefaultCarConfig.Icons.VisualPaint = mINI_ReadHashS(GeneralINI, "Icons", "VisualPaint", "PAINT_MOD_BASE");
	DefaultCarConfig.Icons.VisualVinyls = mINI_ReadHashS(GeneralINI, "Icons", "VisualVinyls", "VISUAL_PART_VINYL");
	DefaultCarConfig.Icons.VisualVinylsCustom = mINI_ReadHashS(GeneralINI, "Icons", "VisualVinylsCustom", "");
	DefaultCarConfig.Icons.VisualRimPaint = mINI_ReadHashS(GeneralINI, "Icons", "VisualRimPaint", "PAINT_MOD_PART_RIMS");
	DefaultCarConfig.Icons.VisualWindowTint = mINI_ReadHashS(GeneralINI, "Icons", "VisualWindowTint", "VISUAL_PART_WINDOW_TINTING");
	DefaultCarConfig.Icons.VisualDecals = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecals", "VISUAL_PART_DECALS");
	DefaultCarConfig.Icons.VisualDecalsWindshield = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield1", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield2", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield3", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield4", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield5", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield6", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield7 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield7", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsWindshield8 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsWindshield8", "DECAL_ZONE_WINDSHIELD");
	DefaultCarConfig.Icons.VisualDecalsRearWindow = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow1", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow2", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow3", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow4", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow5", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow6", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow7 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow7", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsRearWindow8 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRearWindow8", "DECAL_ZONE_REARWINDOW");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor", "DECAL_ZONE_LEFTDOOR");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor1", "DECAL_LEFTDOOR_SLOT1");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor2", "DECAL_LEFTDOOR_SLOT2");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor3", "DECAL_LEFTDOOR_SLOT3");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor4", "DECAL_LEFTDOOR_SLOT4");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor5", "DECAL_LEFTDOOR_SLOT5");
	DefaultCarConfig.Icons.VisualDecalsLeftDoor6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftDoor6", "DECAL_LEFTDOOR_SLOT6");
	DefaultCarConfig.Icons.VisualDecalsRightDoor = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor", "DECAL_ZONE_RIGHTDOOR");
	DefaultCarConfig.Icons.VisualDecalsRightDoor1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor1", "DECAL_RIGHTDOOR_SLOT1");
	DefaultCarConfig.Icons.VisualDecalsRightDoor2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor2", "DECAL_RIGHTDOOR_SLOT2");
	DefaultCarConfig.Icons.VisualDecalsRightDoor3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor3", "DECAL_RIGHTDOOR_SLOT3");
	DefaultCarConfig.Icons.VisualDecalsRightDoor4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor4", "DECAL_RIGHTDOOR_SLOT4");
	DefaultCarConfig.Icons.VisualDecalsRightDoor5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor5", "DECAL_RIGHTDOOR_SLOT5");
	DefaultCarConfig.Icons.VisualDecalsRightDoor6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightDoor6", "DECAL_RIGHTDOOR_SLOT6");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter1", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter2", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter3", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter4", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter5", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter6", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter7 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter7", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsLeftQuarter8 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsLeftQuarter8", "DECAL_ZONE_LEFTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter1 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter1", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter2 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter2", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter3 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter3", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter4 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter4", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter5 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter5", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter6 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter6", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter7 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter7", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualDecalsRightQuarter8 = mINI_ReadHashS(GeneralINI, "Icons", "VisualDecalsRightQuarter8", "DECAL_ZONE_RIGHTPANEL");
	DefaultCarConfig.Icons.VisualNumbers = mINI_ReadHashS(GeneralINI, "Icons", "VisualNumbers", "VISUAL_PART_NUMBERS");
	DefaultCarConfig.Icons.VisualCustomGauges = mINI_ReadHashS(GeneralINI, "Icons", "VisualCustomGauges", "VISUAL_PART_HUDS");
	DefaultCarConfig.Icons.VisualDriver = mINI_ReadHashS(GeneralINI, "Icons", "VisualDriver", "VISUAL_PART_DRIVER");
	DefaultCarConfig.Icons.VisualLicensePlate = mINI_ReadHashS(GeneralINI, "Icons", "VisualLicensePlate", "VISUAL_PART_LICENSE_PLATE");
	DefaultCarConfig.Icons.VisualTires = mINI_ReadHashS(GeneralINI, "Icons", "VisualTires", "VISUAL_PART_TIRE");
	DefaultCarConfig.Icons.VisualNeon = mINI_ReadHashS(GeneralINI, "Icons", "VisualNeon", "VISUAL_PART_NEON");
	DefaultCarConfig.Icons.BackroomParts = mINI_ReadHashS(GeneralINI, "Icons", "BackroomParts", "MARKER_ICON_PARTS");
	DefaultCarConfig.Icons.BackroomPartsBodyKits = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsBodyKits", "MARKER_ICON_PARTS_BODYKITS");
	DefaultCarConfig.Icons.BackroomPartsSpoilers = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsSpoilers", "MARKER_ICON_PARTS_SPOILERS");
	DefaultCarConfig.Icons.BackroomPartsSpoilersCF = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsSpoilersCF", "MARKER_ICON_PARTS_CF_SPOILERS");
	DefaultCarConfig.Icons.BackroomPartsRims = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsRims", "MARKER_ICON_PARTS_RIMS");
	DefaultCarConfig.Icons.BackroomPartsHoods = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsHoods", "MARKER_ICON_PARTS_HOODS");
	DefaultCarConfig.Icons.BackroomPartsHoodsCF = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsHoodsCF", "MARKER_ICON_PARTS_CF_HOODS");
	DefaultCarConfig.Icons.BackroomPartsRoofScoops = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsRoofScoops", "MARKER_ICON_PARTS_ROOFSCOOPS");
	DefaultCarConfig.Icons.BackroomPartsRoofScoopsCF = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPartsRoofScoopsCF", "MARKER_ICON_PARTS_CF_ROOFSCOOPS");
	DefaultCarConfig.Icons.BackroomPerformance = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformance", "MARKER_ICON_PERFORMANCE");
	DefaultCarConfig.Icons.BackroomPerformanceEngine = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceEngine", "MARKER_ICON_PERFORMANCE_ENGINE");
	DefaultCarConfig.Icons.BackroomPerformanceTransmission = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceTransmission", "MARKER_ICON_PERFORMANCE_TRANSMISSION");
	DefaultCarConfig.Icons.BackroomPerformanceChassis = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceChassis", "MARKER_ICON_CHASSIS");
	DefaultCarConfig.Icons.BackroomPerformanceNitrous = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceNitrous", "MARKER_ICON_PERFORMANCE_N2O");
	DefaultCarConfig.Icons.BackroomPerformanceTires = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceTires", "MARKER_ICON_TIRES");
	DefaultCarConfig.Icons.BackroomPerformanceBrakes = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceBrakes", "MARKER_ICON_PERFORMANCE_BRAKES");
	DefaultCarConfig.Icons.BackroomPerformanceTurbo = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceTurbo", "MARKER_ICON_PERFORMANCE_TURBO");
	DefaultCarConfig.Icons.BackroomPerformanceSupercharger = mINI_ReadHashS(GeneralINI, "Icons", "BackroomPerformanceSupercharger", "MARKER_ICON_PERFORMANCE_SUPERCHARGER");
	DefaultCarConfig.Icons.BackroomVisual = mINI_ReadHashS(GeneralINI, "Icons", "BackroomVisual", "MARKER_ICON_VISUAL");
	DefaultCarConfig.Icons.BackroomVisualPaint = mINI_ReadHashS(GeneralINI, "Icons", "BackroomVisualPaint", "MARKER_ICON_VISUAL_PAINT");
	DefaultCarConfig.Icons.BackroomVisualVinyls = mINI_ReadHashS(GeneralINI, "Icons", "BackroomVisualVinyls", "MARKER_ICON_VISUAL_VINYLS");
	DefaultCarConfig.Icons.BackroomVisualDecals = mINI_ReadHashS(GeneralINI, "Icons", "BackroomVisualDecals", "MARKER_ICON_VISUAL_DECALS");
	DefaultCarConfig.Icons.BackroomVisualCustomGauges = mINI_ReadHashS(GeneralINI, "Icons", "BackroomVisualCustomGauges", "MARKER_ICON_VISUAL_HUD");
	DefaultCarConfig.Icons.PerformanceEngineStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceEngineStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEnginePro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEnginePro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceEngineJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceTransmissionStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTransmissionJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTransmissionJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceChassisStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceChassisJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceChassisJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceNitrousStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceNitrousJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceNitrousJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceTiresStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTiresJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTiresJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceBrakesStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceBrakesJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceBrakesJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceTurboStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceTurboJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceTurboJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerStock = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerStock", "PERFORMANCE_ICON_BASE_PACKAGE");
	DefaultCarConfig.Icons.PerformanceSuperchargerStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerSuperStreet = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerSuperStreet", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerRace = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerRace", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerSuperPro = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerSuperPro", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerUltimate = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerUltimate", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceSuperchargerJunkman = mINI_ReadHashS(GeneralINI, "Icons", "PerformanceSuperchargerJunkman", "PERFORMANCE_ICON_PACKAGE_1");
	DefaultCarConfig.Icons.PerformanceEngineLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel1Item1");
	DefaultCarConfig.Icons.PerformanceEngineLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel1Item2");
	DefaultCarConfig.Icons.PerformanceEngineLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel1Item3");
	DefaultCarConfig.Icons.PerformanceEngineLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel2Item1");
	DefaultCarConfig.Icons.PerformanceEngineLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel2Item2");
	DefaultCarConfig.Icons.PerformanceEngineLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel2Item3");
	DefaultCarConfig.Icons.PerformanceEngineLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel3Item1");
	DefaultCarConfig.Icons.PerformanceEngineLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel3Item2");
	DefaultCarConfig.Icons.PerformanceEngineLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel3Item3");
	DefaultCarConfig.Icons.PerformanceEngineLevel4Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel4Item1");
	DefaultCarConfig.Icons.PerformanceEngineLevel4Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel4Item2");
	DefaultCarConfig.Icons.PerformanceEngineLevel4Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel4Item3");
	DefaultCarConfig.Icons.PerformanceEngineLevel2Item1Rotary = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel2Item1Rotary");
	DefaultCarConfig.Icons.PerformanceEngineLevel4Item1Rotary = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel4Item1Rotary");
	DefaultCarConfig.Icons.PerformanceEngineLevel4Item3Castrol = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineLevel4Item3Castrol");
	DefaultCarConfig.Icons.PerformanceEngineJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceEngineJunkmanItem");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel1Item1");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel1Item2");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel1Item3");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel2Item1");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel2Item2");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel2Item3");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel3Item1");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel3Item2");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel3Item3");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel4Item1");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel4Item2");
	DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionLevel4Item3");
	DefaultCarConfig.Icons.PerformanceTransmissionJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTransmissionJunkmanItem");
	DefaultCarConfig.Icons.PerformanceChassisLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel1Item1");
	DefaultCarConfig.Icons.PerformanceChassisLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel1Item2");
	DefaultCarConfig.Icons.PerformanceChassisLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel1Item3");
	DefaultCarConfig.Icons.PerformanceChassisLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel2Item1");
	DefaultCarConfig.Icons.PerformanceChassisLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel2Item2");
	DefaultCarConfig.Icons.PerformanceChassisLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel2Item3");
	DefaultCarConfig.Icons.PerformanceChassisLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel3Item1");
	DefaultCarConfig.Icons.PerformanceChassisLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel3Item2");
	DefaultCarConfig.Icons.PerformanceChassisLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisLevel3Item3");
	DefaultCarConfig.Icons.PerformanceChassisJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceChassisJunkmanItem");
	DefaultCarConfig.Icons.PerformanceNitrousLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel1Item1");
	DefaultCarConfig.Icons.PerformanceNitrousLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel1Item2");
	DefaultCarConfig.Icons.PerformanceNitrousLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel1Item3");
	DefaultCarConfig.Icons.PerformanceNitrousLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel2Item1");
	DefaultCarConfig.Icons.PerformanceNitrousLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel2Item2");
	DefaultCarConfig.Icons.PerformanceNitrousLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel2Item3");
	DefaultCarConfig.Icons.PerformanceNitrousLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel3Item1");
	DefaultCarConfig.Icons.PerformanceNitrousLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel3Item2");
	DefaultCarConfig.Icons.PerformanceNitrousLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousLevel3Item3");
	DefaultCarConfig.Icons.PerformanceNitrousJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceNitrousJunkmanItem");
	DefaultCarConfig.Icons.PerformanceTiresLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel1Item1");
	DefaultCarConfig.Icons.PerformanceTiresLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel1Item2");
	DefaultCarConfig.Icons.PerformanceTiresLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel1Item3");
	DefaultCarConfig.Icons.PerformanceTiresLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel2Item1");
	DefaultCarConfig.Icons.PerformanceTiresLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel2Item2");
	DefaultCarConfig.Icons.PerformanceTiresLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel2Item3");
	DefaultCarConfig.Icons.PerformanceTiresLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel3Item1");
	DefaultCarConfig.Icons.PerformanceTiresLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel3Item2");
	DefaultCarConfig.Icons.PerformanceTiresLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresLevel3Item3");
	DefaultCarConfig.Icons.PerformanceTiresJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTiresJunkmanItem");
	DefaultCarConfig.Icons.PerformanceBrakesLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel1Item1");
	DefaultCarConfig.Icons.PerformanceBrakesLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel1Item2");
	DefaultCarConfig.Icons.PerformanceBrakesLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel1Item3");
	DefaultCarConfig.Icons.PerformanceBrakesLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel2Item1");
	DefaultCarConfig.Icons.PerformanceBrakesLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel2Item2");
	DefaultCarConfig.Icons.PerformanceBrakesLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel2Item3");
	DefaultCarConfig.Icons.PerformanceBrakesLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel3Item1");
	DefaultCarConfig.Icons.PerformanceBrakesLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel3Item2");
	DefaultCarConfig.Icons.PerformanceBrakesLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel3Item3");
	DefaultCarConfig.Icons.PerformanceBrakesLevel4Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel4Item1");
	DefaultCarConfig.Icons.PerformanceBrakesLevel4Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel4Item2");
	DefaultCarConfig.Icons.PerformanceBrakesLevel4Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesLevel4Item3");
	DefaultCarConfig.Icons.PerformanceBrakesJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceBrakesJunkmanItem");
	DefaultCarConfig.Icons.PerformanceTurboLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel1Item1");
	DefaultCarConfig.Icons.PerformanceTurboLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel1Item2");
	DefaultCarConfig.Icons.PerformanceTurboLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel1Item3");
	DefaultCarConfig.Icons.PerformanceTurboLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel2Item1");
	DefaultCarConfig.Icons.PerformanceTurboLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel2Item2");
	DefaultCarConfig.Icons.PerformanceTurboLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel2Item3");
	DefaultCarConfig.Icons.PerformanceTurboLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel3Item1");
	DefaultCarConfig.Icons.PerformanceTurboLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel3Item2");
	DefaultCarConfig.Icons.PerformanceTurboLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboLevel3Item3");
	DefaultCarConfig.Icons.PerformanceTurboJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceTurboJunkmanItem");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel1Item1");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel1Item2");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel1Item3");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel2Item1");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel2Item2");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel2Item3");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item1 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel3Item1");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item2 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel3Item2");
	DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item3 = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerLevel3Item3");
	DefaultCarConfig.Icons.PerformanceSuperchargerJunkmanItem = mINI_ReadHash(GeneralINI, "Icons", "PerformanceSuperchargerJunkmanItem");

	// Names
	DefaultCarConfig.Names.Parts = mINI_ReadHashS(GeneralINI, "Names", "Parts", "CO_PARTS");
	DefaultCarConfig.Names.PartsBodyKits = mINI_ReadHashS(GeneralINI, "Names", "PartsBodyKits", "CO_BODY_KITS");
	DefaultCarConfig.Names.PartsSpoilers = mINI_ReadHashS(GeneralINI, "Names", "PartsSpoilers", "CO_SPOILERS");
	DefaultCarConfig.Names.PartsRims = mINI_ReadHashS(GeneralINI, "Names", "PartsRims", "CO_RIMS");
	DefaultCarConfig.Names.PartsRimsBrand = mINI_ReadHashS(GeneralINI, "Names", "PartsRimsBrand", "CO_RIM_BRAND");
	DefaultCarConfig.Names.PartsRimsCustom = mINI_ReadHashS(GeneralINI, "Names", "PartsRimsCustom");
	DefaultCarConfig.Names.PartsHoods = mINI_ReadHashS(GeneralINI, "Names", "PartsHoods", "CO_HOODS");
	DefaultCarConfig.Names.PartsRoofScoops = mINI_ReadHashS(GeneralINI, "Names", "PartsRoofScoops", "CO_ROOF_SCOOPS");
	DefaultCarConfig.Names.PartsInterior = mINI_ReadHashS(GeneralINI, "Names", "PartsInterior", "CO_INTERIOR");
	DefaultCarConfig.Names.PartsRoof = mINI_ReadHashS(GeneralINI, "Names", "PartsRoof", "CO_ROOF");
	DefaultCarConfig.Names.PartsBrakes = mINI_ReadHashS(GeneralINI, "Names", "PartsBrakes", "CO_BRAKES");
	DefaultCarConfig.Names.PartsHeadlights = mINI_ReadHashS(GeneralINI, "Names", "PartsHeadlights", "CO_HEADLIGHTS");
	DefaultCarConfig.Names.PartsTaillights = mINI_ReadHashS(GeneralINI, "Names", "PartsTaillights", "CO_TAILLIGHTS");
	DefaultCarConfig.Names.PartsMirrors = mINI_ReadHashS(GeneralINI, "Names", "PartsMirrors", "CO_SIDE_MIRROR");
	DefaultCarConfig.Names.PartsAttachments = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachments", "CO_ATTACHMENTS");
	DefaultCarConfig.Names.PartsAttachment0 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment0", "CO_ATTACHMENT_1");
	DefaultCarConfig.Names.PartsAttachment1 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment1", "CO_ATTACHMENT_2");
	DefaultCarConfig.Names.PartsAttachment2 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment2", "CO_ATTACHMENT_3");
	DefaultCarConfig.Names.PartsAttachment3 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment3", "CO_ATTACHMENT_4");
	DefaultCarConfig.Names.PartsAttachment4 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment4", "CO_ATTACHMENT_5");
	DefaultCarConfig.Names.PartsAttachment5 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment5", "CO_ATTACHMENT_6");
	DefaultCarConfig.Names.PartsAttachment6 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment6", "CO_ATTACHMENT_7");
	DefaultCarConfig.Names.PartsAttachment7 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment7", "CO_ATTACHMENT_8");
	DefaultCarConfig.Names.PartsAttachment8 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment8", "CO_ATTACHMENT_9");
	DefaultCarConfig.Names.PartsAttachment9 = mINI_ReadHashS(GeneralINI, "Names", "PartsAttachment9", "CO_ATTACHMENT_10");
	DefaultCarConfig.Names.Performance = mINI_ReadHashS(GeneralINI, "Names", "Performance", "CO_PERFORMANCE");
	DefaultCarConfig.Names.PerformanceEngine = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngine", "CO_ENGINE");
	DefaultCarConfig.Names.PerformanceTransmission = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmission", "CO_TRANSMISSION");
	DefaultCarConfig.Names.PerformanceChassis = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassis", "CO_SUSPENSION");
	DefaultCarConfig.Names.PerformanceNitrous = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrous", "CO_NITROUS");
	DefaultCarConfig.Names.PerformanceTires = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTires", "CO_TIRES");
	DefaultCarConfig.Names.PerformanceBrakes = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakes", "CO_BRAKES");
	DefaultCarConfig.Names.PerformanceTurbo = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurbo", "CO_TURBO");
	DefaultCarConfig.Names.PerformanceSupercharger = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSupercharger", "CO_SUPERCHARGER");
	DefaultCarConfig.Names.Visual = mINI_ReadHashS(GeneralINI, "Names", "Visual", "CO_VISUAL");
	DefaultCarConfig.Names.VisualPaint = mINI_ReadHashS(GeneralINI, "Names", "VisualPaint", "CO_PAINT");
	DefaultCarConfig.Names.VisualPaintCustom = mINI_ReadHashS(GeneralINI, "Names", "VisualPaintCustom");
	DefaultCarConfig.Names.VisualVinyls = mINI_ReadHashS(GeneralINI, "Names", "VisualVinyls", "CO_VINYLS");
	DefaultCarConfig.Names.VisualVinylsCustom = mINI_ReadHashS(GeneralINI, "Names", "VisualVinylsCustom");
	DefaultCarConfig.Names.VisualVinylsGroup = mINI_ReadHashS(GeneralINI, "Names", "VisualVinylsGroup", "CO_VINYL_STYLE");
	DefaultCarConfig.Names.VisualVinylsColor = mINI_ReadHashS(GeneralINI, "Names", "VisualVinylsColor", "CO_VINYL_COLOR");
	DefaultCarConfig.Names.VisualRimPaint = mINI_ReadHashS(GeneralINI, "Names", "VisualRimPaint", "CO_RIM_PAINT");
	DefaultCarConfig.Names.VisualWindowTint = mINI_ReadHashS(GeneralINI, "Names", "VisualWindowTint", "CO_WINDOW_TINT");
	DefaultCarConfig.Names.VisualDecals = mINI_ReadHashS(GeneralINI, "Names", "VisualDecals", "CO_DECALS");
	DefaultCarConfig.Names.VisualDecalsPosition = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsPosition", "CO_DECAL_POSITION");
	DefaultCarConfig.Names.VisualDecalsLocation = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLocation", "CO_DECAL_LOCATION");
	DefaultCarConfig.Names.VisualDecalsWindshield = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield", "CO_DECAL_WINDSHIELD");
	DefaultCarConfig.Names.VisualDecalsWindshield1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsWindshield2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsWindshield3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsWindshield4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsWindshield5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsWindshield6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsWindshield7 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield7", "CO_DECAL_SLOT_7");
	DefaultCarConfig.Names.VisualDecalsWindshield8 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsWindshield8", "CO_DECAL_SLOT_8");
	DefaultCarConfig.Names.VisualDecalsRearWindow = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow", "CO_DECAL_REAR_WINDOW");
	DefaultCarConfig.Names.VisualDecalsRearWindow1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsRearWindow2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsRearWindow3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsRearWindow4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsRearWindow5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsRearWindow6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsRearWindow7 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow7", "CO_DECAL_SLOT_7");
	DefaultCarConfig.Names.VisualDecalsRearWindow8 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRearWindow8", "CO_DECAL_SLOT_8");
	DefaultCarConfig.Names.VisualDecalsLeftDoor = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor", "CO_DECAL_LEFT_DOOR");
	DefaultCarConfig.Names.VisualDecalsLeftDoor1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsLeftDoor2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsLeftDoor3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsLeftDoor4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsLeftDoor5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsLeftDoor6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftDoor6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsRightDoor = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor", "CO_DECAL_RIGHT_DOOR");
	DefaultCarConfig.Names.VisualDecalsRightDoor1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsRightDoor2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsRightDoor3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsRightDoor4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsRightDoor5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsRightDoor6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightDoor6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter", "CO_DECAL_LEFT_QUARTER");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter7 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter7", "CO_DECAL_SLOT_7");
	DefaultCarConfig.Names.VisualDecalsLeftQuarter8 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsLeftQuarter8", "CO_DECAL_SLOT_8");
	DefaultCarConfig.Names.VisualDecalsRightQuarter = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter", "CO_DECAL_RIGHT_QUARTER");
	DefaultCarConfig.Names.VisualDecalsRightQuarter1 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter1", "CO_DECAL_SLOT_1");
	DefaultCarConfig.Names.VisualDecalsRightQuarter2 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter2", "CO_DECAL_SLOT_2");
	DefaultCarConfig.Names.VisualDecalsRightQuarter3 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter3", "CO_DECAL_SLOT_3");
	DefaultCarConfig.Names.VisualDecalsRightQuarter4 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter4", "CO_DECAL_SLOT_4");
	DefaultCarConfig.Names.VisualDecalsRightQuarter5 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter5", "CO_DECAL_SLOT_5");
	DefaultCarConfig.Names.VisualDecalsRightQuarter6 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter6", "CO_DECAL_SLOT_6");
	DefaultCarConfig.Names.VisualDecalsRightQuarter7 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter7", "CO_DECAL_SLOT_7");
	DefaultCarConfig.Names.VisualDecalsRightQuarter8 = mINI_ReadHashS(GeneralINI, "Names", "VisualDecalsRightQuarter8", "CO_DECAL_SLOT_8");
	DefaultCarConfig.Names.VisualNumbers = mINI_ReadHashS(GeneralINI, "Names", "VisualNumbers", "CO_NUMBERS");
	DefaultCarConfig.Names.VisualCustomGauges = mINI_ReadHashS(GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD");
	DefaultCarConfig.Names.VisualDriver = mINI_ReadHashS(GeneralINI, "Names", "VisualDriver", "CO_DRIVER");
	DefaultCarConfig.Names.VisualLicensePlate = mINI_ReadHashS(GeneralINI, "Names", "VisualLicensePlate", "CO_LICENSE_PLATE");
	DefaultCarConfig.Names.VisualTires = mINI_ReadHashS(GeneralINI, "Names", "VisualTires", "CO_TIRES");
	DefaultCarConfig.Names.VisualNeon = mINI_ReadHashS(GeneralINI, "Names", "VisualNeon", "CO_NEON");
	DefaultCarConfig.Names.BackroomParts = mINI_ReadHashS(GeneralINI, "Names", "BackroomParts", "CO_BACKROOM_PARTS");
	DefaultCarConfig.Names.BackroomPerformance = mINI_ReadHashS(GeneralINI, "Names", "BackroomPerformance", "CO_BACKROOM_PERFORMANCE");
	DefaultCarConfig.Names.BackroomVisual = mINI_ReadHashS(GeneralINI, "Names", "BackroomVisual", "CO_BACKROOM_VISUAL");
	DefaultCarConfig.Names.PerformanceEngineStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceEngineStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceEngineSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceEngineRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceEnginePro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEnginePro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceEngineSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceEngineUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceEngineJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTransmissionStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceTransmissionStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceTransmissionSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceTransmissionRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceTransmissionPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceTransmissionSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceTransmissionUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceTransmissionJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceChassisStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceChassisStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceChassisSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceChassisRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceChassisPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceChassisSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceChassisUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceChassisJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceNitrousStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceNitrousStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceNitrousSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceNitrousRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceNitrousPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceNitrousSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceNitrousUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceNitrousJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTiresStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceTiresStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceTiresSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceTiresRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceTiresPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceTiresSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceTiresUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceTiresJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceBrakesStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceBrakesStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceBrakesSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceBrakesRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceBrakesPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceBrakesSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceBrakesUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceBrakesJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTurboStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceTurboStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceTurboSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceTurboRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceTurboPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceTurboSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceTurboUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceTurboJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceSuperchargerStock = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerStock", "PN_LEVEL_0");
	DefaultCarConfig.Names.PerformanceSuperchargerStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerStreet", "PN_LEVEL_1");
	DefaultCarConfig.Names.PerformanceSuperchargerSuperStreet = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerSuperStreet", "PN_LEVEL_2");
	DefaultCarConfig.Names.PerformanceSuperchargerRace = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerRace", "PN_LEVEL_3");
	DefaultCarConfig.Names.PerformanceSuperchargerPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerPro", "PN_LEVEL_4");
	DefaultCarConfig.Names.PerformanceSuperchargerSuperPro = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerSuperPro", "PN_LEVEL_5");
	DefaultCarConfig.Names.PerformanceSuperchargerUltimate = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerUltimate", "PN_LEVEL_6");
	DefaultCarConfig.Names.PerformanceSuperchargerJunkman = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerJunkman", "PN_LEVEL_JUNKMAN");
	DefaultCarConfig.Names.PerformanceEngineLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel1Item1", "PD_ENGINE_1_1");
	DefaultCarConfig.Names.PerformanceEngineLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel1Item2", "PD_ENGINE_1_2");
	DefaultCarConfig.Names.PerformanceEngineLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel1Item3", "PD_ENGINE_1_3");
	DefaultCarConfig.Names.PerformanceEngineLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel2Item1", "PD_ENGINE_2_1");
	DefaultCarConfig.Names.PerformanceEngineLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel2Item2", "PD_ENGINE_2_2");
	DefaultCarConfig.Names.PerformanceEngineLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel2Item3", "PD_ENGINE_2_3");
	DefaultCarConfig.Names.PerformanceEngineLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel3Item1", "PD_ENGINE_3_1");
	DefaultCarConfig.Names.PerformanceEngineLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel3Item2", "PD_ENGINE_3_2");
	DefaultCarConfig.Names.PerformanceEngineLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel3Item3", "PD_ENGINE_3_3");
	DefaultCarConfig.Names.PerformanceEngineLevel4Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel4Item1", "PD_ENGINE_4_1");
	DefaultCarConfig.Names.PerformanceEngineLevel4Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel4Item2", "PD_ENGINE_4_2");
	DefaultCarConfig.Names.PerformanceEngineLevel4Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel4Item3", "PD_ENGINE_4_3");
	DefaultCarConfig.Names.PerformanceEngineLevel2Item1Rotary = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel2Item1Rotary", "PD_ENGINE_2_1_ROTARY");
	DefaultCarConfig.Names.PerformanceEngineLevel4Item1Rotary = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel4Item1Rotary", "PD_ENGINE_4_1_ROTARY");
	DefaultCarConfig.Names.PerformanceEngineLevel4Item3Castrol = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineLevel4Item3Castrol", "PD_ENGINE_4_3_CASTROL");
	DefaultCarConfig.Names.PerformanceEngineJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceEngineJunkmanItem", "PD_ENGINE_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTransmissionLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel1Item1", "PD_TRANSMISSION_1_1");
	DefaultCarConfig.Names.PerformanceTransmissionLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel1Item2", "PD_TRANSMISSION_1_2");
	DefaultCarConfig.Names.PerformanceTransmissionLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel1Item3", "PD_TRANSMISSION_1_3");
	DefaultCarConfig.Names.PerformanceTransmissionLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel2Item1", "PD_TRANSMISSION_2_1");
	DefaultCarConfig.Names.PerformanceTransmissionLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel2Item2", "PD_TRANSMISSION_2_2");
	DefaultCarConfig.Names.PerformanceTransmissionLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel2Item3");
	DefaultCarConfig.Names.PerformanceTransmissionLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel3Item1", "PD_TRANSMISSION_3_1");
	DefaultCarConfig.Names.PerformanceTransmissionLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel3Item2", "PD_TRANSMISSION_3_2");
	DefaultCarConfig.Names.PerformanceTransmissionLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel3Item3");
	DefaultCarConfig.Names.PerformanceTransmissionLevel4Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel4Item1", "PD_TRANSMISSION_4_1");
	DefaultCarConfig.Names.PerformanceTransmissionLevel4Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel4Item2", "PD_TRANSMISSION_4_2");
	DefaultCarConfig.Names.PerformanceTransmissionLevel4Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionLevel4Item3");
	DefaultCarConfig.Names.PerformanceTransmissionJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTransmissionJunkmanItem", "PD_TRANSMISSION_JUNKMAN");
	DefaultCarConfig.Names.PerformanceChassisLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel1Item1", "PD_CHASSIS_1_1");
	DefaultCarConfig.Names.PerformanceChassisLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel1Item2", "PD_CHASSIS_1_2");
	DefaultCarConfig.Names.PerformanceChassisLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel1Item3", "PD_CHASSIS_1_3");
	DefaultCarConfig.Names.PerformanceChassisLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel2Item1", "PD_CHASSIS_2_1");
	DefaultCarConfig.Names.PerformanceChassisLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel2Item2", "PD_CHASSIS_2_2");
	DefaultCarConfig.Names.PerformanceChassisLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel2Item3");
	DefaultCarConfig.Names.PerformanceChassisLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel3Item1", "PD_CHASSIS_3_1");
	DefaultCarConfig.Names.PerformanceChassisLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel3Item2", "PD_CHASSIS_3_2");
	DefaultCarConfig.Names.PerformanceChassisLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisLevel3Item3", "PD_CHASSIS_3_3");
	DefaultCarConfig.Names.PerformanceChassisJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceChassisJunkmanItem", "PD_CHASSIS_JUNKMAN");
	DefaultCarConfig.Names.PerformanceNitrousLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel1Item1", "PD_NITROUS_1_1");
	DefaultCarConfig.Names.PerformanceNitrousLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel1Item2");
	DefaultCarConfig.Names.PerformanceNitrousLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel1Item3");
	DefaultCarConfig.Names.PerformanceNitrousLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel2Item1", "PD_NITROUS_2_1");
	DefaultCarConfig.Names.PerformanceNitrousLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel2Item2");
	DefaultCarConfig.Names.PerformanceNitrousLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel2Item3");
	DefaultCarConfig.Names.PerformanceNitrousLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel3Item1", "PD_NITROUS_3_1");
	DefaultCarConfig.Names.PerformanceNitrousLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel3Item2");
	DefaultCarConfig.Names.PerformanceNitrousLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousLevel3Item3");
	DefaultCarConfig.Names.PerformanceNitrousJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceNitrousJunkmanItem", "PD_NITROUS_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTiresLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel1Item1", "PD_TIRES_1_1");
	DefaultCarConfig.Names.PerformanceTiresLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel1Item2");
	DefaultCarConfig.Names.PerformanceTiresLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel1Item3");
	DefaultCarConfig.Names.PerformanceTiresLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel2Item1", "PD_TIRES_2_1");
	DefaultCarConfig.Names.PerformanceTiresLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel2Item2");
	DefaultCarConfig.Names.PerformanceTiresLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel2Item3");
	DefaultCarConfig.Names.PerformanceTiresLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel3Item1", "PD_TIRES_3_1");
	DefaultCarConfig.Names.PerformanceTiresLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel3Item2");
	DefaultCarConfig.Names.PerformanceTiresLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresLevel3Item3");
	DefaultCarConfig.Names.PerformanceTiresJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTiresJunkmanItem", "PD_TIRES_JUNKMAN");
	DefaultCarConfig.Names.PerformanceBrakesLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel1Item1", "PD_BRAKES_1_1");
	DefaultCarConfig.Names.PerformanceBrakesLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel1Item2", "PD_BRAKES_1_2");
	DefaultCarConfig.Names.PerformanceBrakesLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel1Item3");
	DefaultCarConfig.Names.PerformanceBrakesLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel2Item1", "PD_BRAKES_2_1");
	DefaultCarConfig.Names.PerformanceBrakesLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel2Item2", "PD_BRAKES_2_2");
	DefaultCarConfig.Names.PerformanceBrakesLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel2Item3");
	DefaultCarConfig.Names.PerformanceBrakesLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel3Item1", "PD_BRAKES_3_1");
	DefaultCarConfig.Names.PerformanceBrakesLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel3Item2", "PD_BRAKES_3_2");
	DefaultCarConfig.Names.PerformanceBrakesLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel3Item3");
	DefaultCarConfig.Names.PerformanceBrakesLevel4Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel4Item1", "PD_BRAKES_4_1");
	DefaultCarConfig.Names.PerformanceBrakesLevel4Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel4Item2", "PD_BRAKES_4_2");
	DefaultCarConfig.Names.PerformanceBrakesLevel4Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesLevel4Item3", "PD_BRAKES_4_3");
	DefaultCarConfig.Names.PerformanceBrakesJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceBrakesJunkmanItem", "PD_BRAKES_JUNKMAN");
	DefaultCarConfig.Names.PerformanceTurboLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel1Item1", "PD_TURBO_1_1");
	DefaultCarConfig.Names.PerformanceTurboLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel1Item2", "PD_TURBO_1_2");
	DefaultCarConfig.Names.PerformanceTurboLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel1Item3");
	DefaultCarConfig.Names.PerformanceTurboLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel2Item1", "PD_TURBO_2_1");
	DefaultCarConfig.Names.PerformanceTurboLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel2Item2", "PD_TURBO_2_2");
	DefaultCarConfig.Names.PerformanceTurboLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel2Item3", "PD_TURBO_2_3");
	DefaultCarConfig.Names.PerformanceTurboLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel3Item1", "PD_TURBO_3_1");
	DefaultCarConfig.Names.PerformanceTurboLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel3Item2", "PD_TURBO_3_2");
	DefaultCarConfig.Names.PerformanceTurboLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboLevel3Item3");
	DefaultCarConfig.Names.PerformanceTurboJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceTurboJunkmanItem", "PD_TURBO_JUNKMAN");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel1Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel1Item1", "PD_SUPERCHARGER_1_1");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel1Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel1Item2");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel1Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel1Item3");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel2Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel2Item1", "PD_SUPERCHARGER_2_1");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel2Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel2Item2");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel2Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel2Item3");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel3Item1 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel3Item1", "PD_SUPERCHARGER_3_1");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel3Item2 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel3Item2");
	DefaultCarConfig.Names.PerformanceSuperchargerLevel3Item3 = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerLevel3Item3");
	DefaultCarConfig.Names.PerformanceSuperchargerJunkmanItem = mINI_ReadHashS(GeneralINI, "Names", "PerformanceSuperchargerJunkmanItem", "PD_SUPERCHARGER_JUNKMAN");

	// Cameras
	DefaultCarConfig.Cameras.PartsBodyKits = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsBodyKits");
	DefaultCarConfig.Cameras.PartsSpoilers = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsSpoilers");
	DefaultCarConfig.Cameras.PartsRims = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRims");
	DefaultCarConfig.Cameras.PartsRimsBrand = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRimsBrand");
	DefaultCarConfig.Cameras.PartsRimsBrandRear = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRimsBrandRear");
	DefaultCarConfig.Cameras.PartsRimsBrandAll = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRimsBrandAll");
	DefaultCarConfig.Cameras.PartsHoods = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsHoods");
	DefaultCarConfig.Cameras.PartsRoofScoops = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRoofScoops");
	DefaultCarConfig.Cameras.PartsInterior = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsInterior");
	DefaultCarConfig.Cameras.PartsRoof = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsRoof");
	DefaultCarConfig.Cameras.PartsBrakes = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsBrakes");
	DefaultCarConfig.Cameras.PartsHeadlights = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsHeadlights");
	DefaultCarConfig.Cameras.PartsTaillights = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsTaillights");
	DefaultCarConfig.Cameras.PartsMirrors = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsMirrors");
	DefaultCarConfig.Cameras.PartsAttachments = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachments");
	DefaultCarConfig.Cameras.PartsAttachment0 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment0");
	DefaultCarConfig.Cameras.PartsAttachment1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment1");
	DefaultCarConfig.Cameras.PartsAttachment2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment2");
	DefaultCarConfig.Cameras.PartsAttachment3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment3");
	DefaultCarConfig.Cameras.PartsAttachment4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment4");
	DefaultCarConfig.Cameras.PartsAttachment5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment5");
	DefaultCarConfig.Cameras.PartsAttachment6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment6");
	DefaultCarConfig.Cameras.PartsAttachment7 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment7");
	DefaultCarConfig.Cameras.PartsAttachment8 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment8");
	DefaultCarConfig.Cameras.PartsAttachment9 = mINI_ReadVLTHash(GeneralINI, "Cameras", "PartsAttachment9");
	DefaultCarConfig.Cameras.VisualPaint = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualPaint");
	DefaultCarConfig.Cameras.VisualVinyls = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualVinyls");
	DefaultCarConfig.Cameras.VisualVinylsGroup = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualVinylsGroup");
	DefaultCarConfig.Cameras.VisualRimPaint = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualRimPaint");
	DefaultCarConfig.Cameras.VisualWindowTint = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualWindowTint");
	DefaultCarConfig.Cameras.VisualDecals = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecals");
	DefaultCarConfig.Cameras.VisualDecalsWindshield = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield");
	DefaultCarConfig.Cameras.VisualDecalsWindshield1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield1");
	DefaultCarConfig.Cameras.VisualDecalsWindshield2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield2");
	DefaultCarConfig.Cameras.VisualDecalsWindshield3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield3");
	DefaultCarConfig.Cameras.VisualDecalsWindshield4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield4");
	DefaultCarConfig.Cameras.VisualDecalsWindshield5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield5");
	DefaultCarConfig.Cameras.VisualDecalsWindshield6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield6");
	DefaultCarConfig.Cameras.VisualDecalsWindshield7 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield7");
	DefaultCarConfig.Cameras.VisualDecalsWindshield8 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsWindshield8");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow1");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow2");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow3");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow4");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow5");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow6");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow7 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow7");
	DefaultCarConfig.Cameras.VisualDecalsRearWindow8 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRearWindow8");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor1");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor2");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor3");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor4");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor5");
	DefaultCarConfig.Cameras.VisualDecalsLeftDoor6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftDoor6");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor1");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor2");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor3");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor4");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor5");
	DefaultCarConfig.Cameras.VisualDecalsRightDoor6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightDoor6");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter1");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter2");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter3");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter4");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter5");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter6");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter7 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter7");
	DefaultCarConfig.Cameras.VisualDecalsLeftQuarter8 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsLeftQuarter8");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter1 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter1");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter2 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter2");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter3 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter3");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter4 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter4");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter5 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter5");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter6 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter6");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter7 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter7");
	DefaultCarConfig.Cameras.VisualDecalsRightQuarter8 = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDecalsRightQuarter8");
	DefaultCarConfig.Cameras.VisualNumbers = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualNumbers");
	DefaultCarConfig.Cameras.VisualCustomGauges = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualCustomGauges");
	DefaultCarConfig.Cameras.VisualDriver = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualDriver");
	DefaultCarConfig.Cameras.VisualLicensePlate = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualLicensePlate");
	DefaultCarConfig.Cameras.VisualTires = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualTires");
	DefaultCarConfig.Cameras.VisualNeon = mINI_ReadVLTHash(GeneralINI, "Cameras", "VisualNeon");

	// StockParts
	DefaultCarConfig.StockParts.CustomStockParts = mINI_ReadInteger(GeneralINI, "StockParts", "CustomStockParts", 0) != 0;
	for (int p = 0; p < NumCarSlots; p++) DefaultCarConfig.StockParts.Parts[p] = -1;

	DefaultCarConfig.StockParts.Parts[23] = mINI_ReadHash(GeneralINI, "StockParts", "BodyKits"); // BODY
	DefaultCarConfig.StockParts.Parts[44] = mINI_ReadHash(GeneralINI, "StockParts", "Spoilers"); // SPOILER
	DefaultCarConfig.StockParts.Parts[66] = mINI_ReadHash(GeneralINI, "StockParts", "RimsFront"); // FRONT_WHEEL
	DefaultCarConfig.StockParts.Parts[67] = mINI_ReadHash(GeneralINI, "StockParts", "RimsRear"); // REAR_WHEEL
	DefaultCarConfig.StockParts.Parts[63] = mINI_ReadHash(GeneralINI, "StockParts", "Hoods"); // HOOD
	DefaultCarConfig.StockParts.Parts[62] = mINI_ReadHash(GeneralINI, "StockParts", "RoofScoops"); // ROOF
	DefaultCarConfig.StockParts.Parts[28] = mINI_ReadHash(GeneralINI, "StockParts", "Interior"); // INTERIOR
	DefaultCarConfig.StockParts.Parts[0] = mINI_ReadHash(GeneralINI, "StockParts", "Roof"); // BASE
	DefaultCarConfig.StockParts.Parts[24] = mINI_ReadHash(GeneralINI, "StockParts", "Brakes"); // FRONT_BRAKE
	DefaultCarConfig.StockParts.Parts[31] = mINI_ReadHash(GeneralINI, "StockParts", "Headlights"); // LEFT_HEADLIGHT
	DefaultCarConfig.StockParts.Parts[29] = mINI_ReadHash(GeneralINI, "StockParts", "Taillights"); // LEFT_BRAKELIGHT
	DefaultCarConfig.StockParts.Parts[33] = mINI_ReadHash(GeneralINI, "StockParts", "Mirrors"); // LEFT_SIDE_MIRROR
	DefaultCarConfig.StockParts.Parts[52] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment0"); // ATTACHMENT0
	DefaultCarConfig.StockParts.Parts[53] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment1"); // ATTACHMENT1
	DefaultCarConfig.StockParts.Parts[54] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment2"); // ATTACHMENT2
	DefaultCarConfig.StockParts.Parts[55] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment3"); // ATTACHMENT3
	DefaultCarConfig.StockParts.Parts[56] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment4"); // ATTACHMENT4
	DefaultCarConfig.StockParts.Parts[57] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment5"); // ATTACHMENT5
	DefaultCarConfig.StockParts.Parts[58] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment6"); // ATTACHMENT6
	DefaultCarConfig.StockParts.Parts[59] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment7"); // ATTACHMENT7
	DefaultCarConfig.StockParts.Parts[60] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment8"); // ATTACHMENT8
	DefaultCarConfig.StockParts.Parts[61] = mINI_ReadHash(GeneralINI, "StockParts", "Attachment9"); // ATTACHMENT9
	DefaultCarConfig.StockParts.Parts[76] = mINI_ReadHash(GeneralINI, "StockParts", "Paint"); // BASE_PAINT
	DefaultCarConfig.StockParts.Parts[77] = mINI_ReadHash(GeneralINI, "StockParts", "Vinyls"); // VINYL_LAYER0
	DefaultCarConfig.StockParts.Parts[79] = mINI_ReadHash(GeneralINI, "StockParts", "VinylColor1");  // VINYL_COLOUR0_0
	DefaultCarConfig.StockParts.Parts[80] = mINI_ReadHash(GeneralINI, "StockParts", "VinylColor2");  // VINYL_COLOUR0_1
	DefaultCarConfig.StockParts.Parts[81] = mINI_ReadHash(GeneralINI, "StockParts", "VinylColor3");  // VINYL_COLOUR0_2
	DefaultCarConfig.StockParts.Parts[82] = mINI_ReadHash(GeneralINI, "StockParts", "VinylColor4");  // VINYL_COLOUR0_3
	DefaultCarConfig.StockParts.Parts[78] = mINI_ReadHash(GeneralINI, "StockParts", "RimPaint"); // PAINT_RIM
	DefaultCarConfig.StockParts.Parts[131] = mINI_ReadHash(GeneralINI, "StockParts", "WindowTint"); // WINDOW_TINT
	DefaultCarConfig.StockParts.Parts[83] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield1"); // DECAL_FRONT_WINDOW_TEX0
	DefaultCarConfig.StockParts.Parts[84] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield2"); // DECAL_FRONT_WINDOW_TEX1
	DefaultCarConfig.StockParts.Parts[85] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield3"); // DECAL_FRONT_WINDOW_TEX2
	DefaultCarConfig.StockParts.Parts[86] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield4"); // DECAL_FRONT_WINDOW_TEX3
	DefaultCarConfig.StockParts.Parts[87] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield5"); // DECAL_FRONT_WINDOW_TEX4
	DefaultCarConfig.StockParts.Parts[88] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield6"); // DECAL_FRONT_WINDOW_TEX5
	DefaultCarConfig.StockParts.Parts[89] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield7"); // DECAL_FRONT_WINDOW_TEX6
	DefaultCarConfig.StockParts.Parts[90] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsWindshield8"); // DECAL_FRONT_WINDOW_TEX7
	DefaultCarConfig.StockParts.Parts[91] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow1"); // DECAL_REAR_WINDOW_TEX0
	DefaultCarConfig.StockParts.Parts[92] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow2"); // DECAL_REAR_WINDOW_TEX1
	DefaultCarConfig.StockParts.Parts[93] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow3"); // DECAL_REAR_WINDOW_TEX2
	DefaultCarConfig.StockParts.Parts[94] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow4"); // DECAL_REAR_WINDOW_TEX3
	DefaultCarConfig.StockParts.Parts[95] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow5"); // DECAL_REAR_WINDOW_TEX4
	DefaultCarConfig.StockParts.Parts[96] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow6"); // DECAL_REAR_WINDOW_TEX5
	DefaultCarConfig.StockParts.Parts[97] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow7"); // DECAL_REAR_WINDOW_TEX6
	DefaultCarConfig.StockParts.Parts[98] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRearWindow8"); // DECAL_REAR_WINDOW_TEX7
	DefaultCarConfig.StockParts.Parts[99] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor1"); // DECAL_LEFT_DOOR_TEX0
	DefaultCarConfig.StockParts.Parts[100] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor2"); // DECAL_LEFT_DOOR_TEX1
	DefaultCarConfig.StockParts.Parts[101] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor3"); // DECAL_LEFT_DOOR_TEX2
	DefaultCarConfig.StockParts.Parts[102] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor4"); // DECAL_LEFT_DOOR_TEX3
	DefaultCarConfig.StockParts.Parts[103] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor5"); // DECAL_LEFT_DOOR_TEX4
	DefaultCarConfig.StockParts.Parts[104] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftDoor6"); // DECAL_LEFT_DOOR_TEX5
	DefaultCarConfig.StockParts.Parts[107] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor1"); // DECAL_RIGHT_DOOR_TEX0
	DefaultCarConfig.StockParts.Parts[108] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor2"); // DECAL_RIGHT_DOOR_TEX1
	DefaultCarConfig.StockParts.Parts[109] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor3"); // DECAL_RIGHT_DOOR_TEX2
	DefaultCarConfig.StockParts.Parts[110] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor4"); // DECAL_RIGHT_DOOR_TEX3
	DefaultCarConfig.StockParts.Parts[111] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor5"); // DECAL_RIGHT_DOOR_TEX4
	DefaultCarConfig.StockParts.Parts[112] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightDoor6"); // DECAL_RIGHT_DOOR_TEX5
	DefaultCarConfig.StockParts.Parts[115] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter1"); // DECAL_LEFT_QUARTER_TEX0
	DefaultCarConfig.StockParts.Parts[116] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter2"); // DECAL_LEFT_QUARTER_TEX1
	DefaultCarConfig.StockParts.Parts[117] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter3"); // DECAL_LEFT_QUARTER_TEX2
	DefaultCarConfig.StockParts.Parts[118] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter4"); // DECAL_LEFT_QUARTER_TEX3
	DefaultCarConfig.StockParts.Parts[119] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter5"); // DECAL_LEFT_QUARTER_TEX4
	DefaultCarConfig.StockParts.Parts[120] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter6"); // DECAL_LEFT_QUARTER_TEX5
	DefaultCarConfig.StockParts.Parts[121] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter7"); // DECAL_LEFT_QUARTER_TEX6
	DefaultCarConfig.StockParts.Parts[122] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsLeftQuarter8"); // DECAL_LEFT_QUARTER_TEX7
	DefaultCarConfig.StockParts.Parts[123] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter1"); // DECAL_RIGHT_QUARTER_TEX0
	DefaultCarConfig.StockParts.Parts[124] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter2"); // DECAL_RIGHT_QUARTER_TEX1
	DefaultCarConfig.StockParts.Parts[125] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter3"); // DECAL_RIGHT_QUARTER_TEX2
	DefaultCarConfig.StockParts.Parts[126] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter4"); // DECAL_RIGHT_QUARTER_TEX3
	DefaultCarConfig.StockParts.Parts[127] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter5"); // DECAL_RIGHT_QUARTER_TEX4
	DefaultCarConfig.StockParts.Parts[128] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter6"); // DECAL_RIGHT_QUARTER_TEX5
	DefaultCarConfig.StockParts.Parts[129] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter7"); // DECAL_RIGHT_QUARTER_TEX6
	DefaultCarConfig.StockParts.Parts[130] = mINI_ReadHash(GeneralINI, "StockParts", "DecalsRightQuarter8"); // DECAL_RIGHT_QUARTER_TEX7
	DefaultCarConfig.StockParts.Parts[105] = mINI_ReadHash(GeneralINI, "StockParts", "NumbersLeftL"); // DECAL_LEFT_DOOR_TEX6
	DefaultCarConfig.StockParts.Parts[106] = mINI_ReadHash(GeneralINI, "StockParts", "NumbersLeftR"); // DECAL_LEFT_DOOR_TEX7
	DefaultCarConfig.StockParts.Parts[113] = mINI_ReadHash(GeneralINI, "StockParts", "NumbersRightL"); // DECAL_RIGHT_DOOR_TEX6
	DefaultCarConfig.StockParts.Parts[114] = mINI_ReadHash(GeneralINI, "StockParts", "NumbersRightR"); // DECAL_RIGHT_DOOR_TEX7
	DefaultCarConfig.StockParts.Parts[132] = mINI_ReadHash(GeneralINI, "StockParts", "CustomGauges"); // CUSTOM_HUD
	DefaultCarConfig.StockParts.Parts[133] = mINI_ReadHash(GeneralINI, "StockParts", "CustomGaugesBackingColor"); // HUD_BACKING_COLOUR
	DefaultCarConfig.StockParts.Parts[134] = mINI_ReadHash(GeneralINI, "StockParts", "CustomGaugesNeedleColor"); // HUD_NEEDLE_COLOUR
	DefaultCarConfig.StockParts.Parts[135] = mINI_ReadHash(GeneralINI, "StockParts", "CustomGaugesCharacterColor"); // HUD_CHARACTER_COLOUR
	DefaultCarConfig.StockParts.Parts[43] = mINI_ReadHash(GeneralINI, "StockParts", "Driver"); // DRIVER
	DefaultCarConfig.StockParts.Parts[69] = mINI_ReadHash(GeneralINI, "StockParts", "LicensePlate"); // LICENSE_PLATE
	DefaultCarConfig.StockParts.Parts[64] = mINI_ReadHash(GeneralINI, "StockParts", "Tires"); // HEADLIGHT (Tires)
	DefaultCarConfig.StockParts.Parts[65] = mINI_ReadHash(GeneralINI, "StockParts", "Neon"); // BRAKELIGHT (Neon)

	// RandomParts
	DefaultCarConfig.RandomParts.ForceCustomizationLevel = mINI_ReadInteger(GeneralINI, "RandomParts", "ForceCustomizationLevel", -2);
	DefaultCarConfig.RandomParts.CustomRandomParts = mINI_ReadInteger(GeneralINI, "RandomParts", "CustomRandomParts", 0) != 0;
	DefaultCarConfig.RandomParts.RandomizeInTraffic = mINI_ReadInteger(GeneralINI, "RandomParts", "RandomizeInTraffic", 0) != 0;
	for (int p = 0; p < NumCarSlots; p++) DefaultCarConfig.RandomParts.Parts[p] = 0;

	DefaultCarConfig.RandomParts.Parts[23] = mINI_ReadInteger(GeneralINI, "RandomParts", "BodyKits", 0) != 0; // BODY
	DefaultCarConfig.RandomParts.Parts[44] = mINI_ReadInteger(GeneralINI, "RandomParts", "Spoilers", 0) != 0; // SPOILER
	DefaultCarConfig.RandomParts.Parts[66] = mINI_ReadInteger(GeneralINI, "RandomParts", "RimsFront", 0) != 0; // FRONT_WHEEL
	DefaultCarConfig.RandomParts.Parts[67] = mINI_ReadInteger(GeneralINI, "RandomParts", "RimsRear", 0) != 0; // REAR_WHEEL
	DefaultCarConfig.RandomParts.Parts[63] = mINI_ReadInteger(GeneralINI, "RandomParts", "Hoods", 0) != 0; // HOOD
	DefaultCarConfig.RandomParts.Parts[62] = mINI_ReadInteger(GeneralINI, "RandomParts", "RoofScoops", 0) != 0; // ROOF
	DefaultCarConfig.RandomParts.Parts[28] = mINI_ReadInteger(GeneralINI, "RandomParts", "Interior", 0) != 0; // INTERIOR
	DefaultCarConfig.RandomParts.Parts[0] = mINI_ReadInteger(GeneralINI, "RandomParts", "Roof", 0) != 0; // BASE
	DefaultCarConfig.RandomParts.Parts[24] = mINI_ReadInteger(GeneralINI, "RandomParts", "Brakes", 0) != 0; // FRONT_BRAKE
	DefaultCarConfig.RandomParts.Parts[31] = mINI_ReadInteger(GeneralINI, "RandomParts", "Headlights", 0) != 0; // LEFT_HEADLIGHT
	DefaultCarConfig.RandomParts.Parts[29] = mINI_ReadInteger(GeneralINI, "RandomParts", "Taillights", 0) != 0; // LEFT_BRAKELIGHT
	DefaultCarConfig.RandomParts.Parts[33] = mINI_ReadInteger(GeneralINI, "RandomParts", "Mirrors", 0) != 0; // LEFT_SIDE_MIRROR
	DefaultCarConfig.RandomParts.Parts[52] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment0", 0) != 0; // ATTACHMENT0
	DefaultCarConfig.RandomParts.Parts[53] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment1", 0) != 0; // ATTACHMENT1
	DefaultCarConfig.RandomParts.Parts[54] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment2", 0) != 0; // ATTACHMENT2
	DefaultCarConfig.RandomParts.Parts[55] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment3", 0) != 0; // ATTACHMENT3
	DefaultCarConfig.RandomParts.Parts[56] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment4", 0) != 0; // ATTACHMENT4
	DefaultCarConfig.RandomParts.Parts[57] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment5", 0) != 0; // ATTACHMENT5
	DefaultCarConfig.RandomParts.Parts[58] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment6", 0) != 0; // ATTACHMENT6
	DefaultCarConfig.RandomParts.Parts[59] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment7", 0) != 0; // ATTACHMENT7
	DefaultCarConfig.RandomParts.Parts[60] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment8", 0) != 0; // ATTACHMENT8
	DefaultCarConfig.RandomParts.Parts[61] = mINI_ReadInteger(GeneralINI, "RandomParts", "Attachment9", 0) != 0; // ATTACHMENT9
	DefaultCarConfig.RandomParts.Parts[76] = mINI_ReadInteger(GeneralINI, "RandomParts", "Paint", 0) != 0; // BASE_PAINT
	DefaultCarConfig.RandomParts.Parts[77] = mINI_ReadInteger(GeneralINI, "RandomParts", "Vinyls", 0) != 0; // VINYL_LAYER0
	DefaultCarConfig.RandomParts.Parts[79] = mINI_ReadInteger(GeneralINI, "RandomParts", "VinylColor1", 0) != 0;  // VINYL_COLOUR0_0
	DefaultCarConfig.RandomParts.Parts[80] = mINI_ReadInteger(GeneralINI, "RandomParts", "VinylColor2", 0) != 0;  // VINYL_COLOUR0_1
	DefaultCarConfig.RandomParts.Parts[81] = mINI_ReadInteger(GeneralINI, "RandomParts", "VinylColor3", 0) != 0;  // VINYL_COLOUR0_2
	DefaultCarConfig.RandomParts.Parts[82] = mINI_ReadInteger(GeneralINI, "RandomParts", "VinylColor4", 0) != 0;  // VINYL_COLOUR0_3
	DefaultCarConfig.RandomParts.Parts[78] = mINI_ReadInteger(GeneralINI, "RandomParts", "RimPaint", 0) != 0; // PAINT_RIM
	DefaultCarConfig.RandomParts.Parts[131] = mINI_ReadInteger(GeneralINI, "RandomParts", "WindowTint", 0) != 0; // WINDOW_TINT
	DefaultCarConfig.RandomParts.Parts[83] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield1", 0) != 0; // DECAL_FRONT_WINDOW_TEX0
	DefaultCarConfig.RandomParts.Parts[84] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield2", 0) != 0; // DECAL_FRONT_WINDOW_TEX1
	DefaultCarConfig.RandomParts.Parts[85] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield3", 0) != 0; // DECAL_FRONT_WINDOW_TEX2
	DefaultCarConfig.RandomParts.Parts[86] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield4", 0) != 0; // DECAL_FRONT_WINDOW_TEX3
	DefaultCarConfig.RandomParts.Parts[87] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield5", 0) != 0; // DECAL_FRONT_WINDOW_TEX4
	DefaultCarConfig.RandomParts.Parts[88] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield6", 0) != 0; // DECAL_FRONT_WINDOW_TEX5
	DefaultCarConfig.RandomParts.Parts[89] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield7", 0) != 0; // DECAL_FRONT_WINDOW_TEX6
	DefaultCarConfig.RandomParts.Parts[90] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsWindshield8", 0) != 0; // DECAL_FRONT_WINDOW_TEX7
	DefaultCarConfig.RandomParts.Parts[91] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow1", 0) != 0; // DECAL_REAR_WINDOW_TEX0
	DefaultCarConfig.RandomParts.Parts[92] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow2", 0) != 0; // DECAL_REAR_WINDOW_TEX1
	DefaultCarConfig.RandomParts.Parts[93] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow3", 0) != 0; // DECAL_REAR_WINDOW_TEX2
	DefaultCarConfig.RandomParts.Parts[94] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow4", 0) != 0; // DECAL_REAR_WINDOW_TEX3
	DefaultCarConfig.RandomParts.Parts[95] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow5", 0) != 0; // DECAL_REAR_WINDOW_TEX4
	DefaultCarConfig.RandomParts.Parts[96] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow6", 0) != 0; // DECAL_REAR_WINDOW_TEX5
	DefaultCarConfig.RandomParts.Parts[97] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow7", 0) != 0; // DECAL_REAR_WINDOW_TEX6
	DefaultCarConfig.RandomParts.Parts[98] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRearWindow8", 0) != 0; // DECAL_REAR_WINDOW_TEX7
	DefaultCarConfig.RandomParts.Parts[99] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor1", 0) != 0; // DECAL_LEFT_DOOR_TEX0
	DefaultCarConfig.RandomParts.Parts[100] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor2", 0) != 0; // DECAL_LEFT_DOOR_TEX1
	DefaultCarConfig.RandomParts.Parts[101] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor3", 0) != 0; // DECAL_LEFT_DOOR_TEX2
	DefaultCarConfig.RandomParts.Parts[102] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor4", 0) != 0; // DECAL_LEFT_DOOR_TEX3
	DefaultCarConfig.RandomParts.Parts[103] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor5", 0) != 0; // DECAL_LEFT_DOOR_TEX4
	DefaultCarConfig.RandomParts.Parts[104] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftDoor6", 0) != 0; // DECAL_LEFT_DOOR_TEX5
	DefaultCarConfig.RandomParts.Parts[107] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor1", 0) != 0; // DECAL_RIGHT_DOOR_TEX0
	DefaultCarConfig.RandomParts.Parts[108] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor2", 0) != 0; // DECAL_RIGHT_DOOR_TEX1
	DefaultCarConfig.RandomParts.Parts[109] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor3", 0) != 0; // DECAL_RIGHT_DOOR_TEX2
	DefaultCarConfig.RandomParts.Parts[110] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor4", 0) != 0; // DECAL_RIGHT_DOOR_TEX3
	DefaultCarConfig.RandomParts.Parts[111] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor5", 0) != 0; // DECAL_RIGHT_DOOR_TEX4
	DefaultCarConfig.RandomParts.Parts[112] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightDoor6", 0) != 0; // DECAL_RIGHT_DOOR_TEX5
	DefaultCarConfig.RandomParts.Parts[115] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter1", 0) != 0; // DECAL_LEFT_QUARTER_TEX0
	DefaultCarConfig.RandomParts.Parts[116] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter2", 0) != 0; // DECAL_LEFT_QUARTER_TEX1
	DefaultCarConfig.RandomParts.Parts[117] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter3", 0) != 0; // DECAL_LEFT_QUARTER_TEX2
	DefaultCarConfig.RandomParts.Parts[118] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter4", 0) != 0; // DECAL_LEFT_QUARTER_TEX3
	DefaultCarConfig.RandomParts.Parts[119] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter5", 0) != 0; // DECAL_LEFT_QUARTER_TEX4
	DefaultCarConfig.RandomParts.Parts[120] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter6", 0) != 0; // DECAL_LEFT_QUARTER_TEX5
	DefaultCarConfig.RandomParts.Parts[121] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter7", 0) != 0; // DECAL_LEFT_QUARTER_TEX6
	DefaultCarConfig.RandomParts.Parts[122] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsLeftQuarter8", 0) != 0; // DECAL_LEFT_QUARTER_TEX7
	DefaultCarConfig.RandomParts.Parts[123] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter1", 0) != 0; // DECAL_RIGHT_QUARTER_TEX0
	DefaultCarConfig.RandomParts.Parts[124] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter2", 0) != 0; // DECAL_RIGHT_QUARTER_TEX1
	DefaultCarConfig.RandomParts.Parts[125] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter3", 0) != 0; // DECAL_RIGHT_QUARTER_TEX2
	DefaultCarConfig.RandomParts.Parts[126] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter4", 0) != 0; // DECAL_RIGHT_QUARTER_TEX3
	DefaultCarConfig.RandomParts.Parts[127] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter5", 0) != 0; // DECAL_RIGHT_QUARTER_TEX4
	DefaultCarConfig.RandomParts.Parts[128] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter6", 0) != 0; // DECAL_RIGHT_QUARTER_TEX5
	DefaultCarConfig.RandomParts.Parts[129] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter7", 0) != 0; // DECAL_RIGHT_QUARTER_TEX6
	DefaultCarConfig.RandomParts.Parts[130] = mINI_ReadInteger(GeneralINI, "RandomParts", "DecalsRightQuarter8", 0) != 0; // DECAL_RIGHT_QUARTER_TEX7
	DefaultCarConfig.RandomParts.Parts[105] = mINI_ReadInteger(GeneralINI, "RandomParts", "NumbersLeftL", 0) != 0; // DECAL_LEFT_DOOR_TEX6
	DefaultCarConfig.RandomParts.Parts[106] = mINI_ReadInteger(GeneralINI, "RandomParts", "NumbersLeftR", 0) != 0; // DECAL_LEFT_DOOR_TEX7
	DefaultCarConfig.RandomParts.Parts[113] = mINI_ReadInteger(GeneralINI, "RandomParts", "NumbersRightL", 0) != 0; // DECAL_RIGHT_DOOR_TEX6
	DefaultCarConfig.RandomParts.Parts[114] = mINI_ReadInteger(GeneralINI, "RandomParts", "NumbersRightR", 0) != 0; // DECAL_RIGHT_DOOR_TEX7
	DefaultCarConfig.RandomParts.Parts[132] = mINI_ReadInteger(GeneralINI, "RandomParts", "CustomGauges", 0) != 0; // CUSTOM_HUD
	DefaultCarConfig.RandomParts.Parts[133] = mINI_ReadInteger(GeneralINI, "RandomParts", "CustomGaugesBackingColor", 0) != 0; // HUD_BACKING_COLOUR
	DefaultCarConfig.RandomParts.Parts[134] = mINI_ReadInteger(GeneralINI, "RandomParts", "CustomGaugesNeedleColor", 0) != 0; // HUD_NEEDLE_COLOUR
	DefaultCarConfig.RandomParts.Parts[135] = mINI_ReadInteger(GeneralINI, "RandomParts", "CustomGaugesCharacterColor", 0) != 0; // HUD_CHARACTER_COLOUR
	DefaultCarConfig.RandomParts.Parts[43] = mINI_ReadInteger(GeneralINI, "RandomParts", "Driver", 0) != 0; // DRIVER
	DefaultCarConfig.RandomParts.Parts[69] = mINI_ReadInteger(GeneralINI, "RandomParts", "LicensePlate", 0) != 0; // LICENSE_PLATE
	DefaultCarConfig.RandomParts.Parts[64] = mINI_ReadInteger(GeneralINI, "RandomParts", "Tires", 0) != 0; // HEADLIGHT (Tires)
	DefaultCarConfig.RandomParts.Parts[65] = mINI_ReadInteger(GeneralINI, "RandomParts", "Neon", 0) != 0; // BRAKELIGHT (Neon)

	// FECooling
	DefaultCarConfig.FECooling.BodyKits = mINI_ReadFloat(GeneralINI, "FECooling", "BodyKits", 0.0f);
	DefaultCarConfig.FECooling.Spoilers = mINI_ReadFloat(GeneralINI, "FECooling", "Spoilers", 0.0f);
	DefaultCarConfig.FECooling.Rims = mINI_ReadFloat(GeneralINI, "FECooling", "Rims", 0.0f);
	DefaultCarConfig.FECooling.Hoods = mINI_ReadFloat(GeneralINI, "FECooling", "Hoods", 0.0f);
	DefaultCarConfig.FECooling.RoofScoops = mINI_ReadFloat(GeneralINI, "FECooling", "RoofScoops", 0.0f);
	DefaultCarConfig.FECooling.Interior = mINI_ReadFloat(GeneralINI, "FECooling", "Interior", 0.98f);
	DefaultCarConfig.FECooling.Roof = mINI_ReadFloat(GeneralINI, "FECooling", "Roof", 0.75f);
	DefaultCarConfig.FECooling.Brakes = mINI_ReadFloat(GeneralINI, "FECooling", "Brakes", 0.98f);
	DefaultCarConfig.FECooling.Headlights = mINI_ReadFloat(GeneralINI, "FECooling", "Headlights", 0.9f);
	DefaultCarConfig.FECooling.Taillights = mINI_ReadFloat(GeneralINI, "FECooling", "Taillights", 0.9f);
	DefaultCarConfig.FECooling.Mirrors = mINI_ReadFloat(GeneralINI, "FECooling", "Mirrors", 0.9f);
	DefaultCarConfig.FECooling.Attachment0 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment0", 0.95f);
	DefaultCarConfig.FECooling.Attachment1 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment1", 0.95f);
	DefaultCarConfig.FECooling.Attachment2 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment2", 0.95f);
	DefaultCarConfig.FECooling.Attachment3 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment3", 0.95f);
	DefaultCarConfig.FECooling.Attachment4 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment4", 0.95f);
	DefaultCarConfig.FECooling.Attachment5 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment5", 0.95f);
	DefaultCarConfig.FECooling.Attachment6 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment6", 0.95f);
	DefaultCarConfig.FECooling.Attachment7 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment7", 0.95f);
	DefaultCarConfig.FECooling.Attachment8 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment8", 0.95f);
	DefaultCarConfig.FECooling.Attachment9 = mINI_ReadFloat(GeneralINI, "FECooling", "Attachment9", 0.95f);
	DefaultCarConfig.FECooling.Paint = mINI_ReadFloat(GeneralINI, "FECooling", "Paint", 0.0f);
	DefaultCarConfig.FECooling.Vinyls = mINI_ReadFloat(GeneralINI, "FECooling", "Vinyls", 0.0f);
	DefaultCarConfig.FECooling.RimPaint = mINI_ReadFloat(GeneralINI, "FECooling", "RimPaint", 0.0f);
	DefaultCarConfig.FECooling.WindowTint = mINI_ReadFloat(GeneralINI, "FECooling", "WindowTint", 0.0f);
	DefaultCarConfig.FECooling.Decals = mINI_ReadFloat(GeneralINI, "FECooling", "Decals", 0.0f);
	DefaultCarConfig.FECooling.Driver = mINI_ReadFloat(GeneralINI, "FECooling", "Driver", 0.9f);
	DefaultCarConfig.FECooling.LicensePlate = mINI_ReadFloat(GeneralINI, "FECooling", "LicensePlate", 0.75f);
	DefaultCarConfig.FECooling.Tires = mINI_ReadFloat(GeneralINI, "FECooling", "Tires", 0.99f);
	DefaultCarConfig.FECooling.Neon = mINI_ReadFloat(GeneralINI, "FECooling", "Neon", 0.95f);

	// Read other cars' configs
	for (int i = 0; i < CarCount; i++)
	{
		ACarConfig.CarTypeInfo = (DWORD*)((*(DWORD*)CarTypeInfoArray) + i * SingleCarTypeInfoBlockSize);
		sprintf(CarININame, "%s.ini", (char*)ACarConfig.CarTypeInfo);
		auto CarINIPath = CurrentWorkingDirectory / "UnlimiterData" / CarININame;
		mINI::INIFile CarINIFile(CarINIPath.string());
		mINI::INIStructure CarINI;
		CarINIFile.read(CarINI);

		// Read config
		// Main
		ACarConfig.Main.ForceLODA = mINI_ReadInteger(CarINI, "Main", "ForceLODA", DefaultCarConfig.Main.ForceLODA) != 0;
		ACarConfig.Main.InitiallyUnlocked = mINI_ReadInteger(CarINI, "Main", "InitiallyUnlocked", DefaultCarConfig.Main.InitiallyUnlocked);
		ACarConfig.Main.EngineType = mINI_ReadInteger(CarINI, "Main", "EngineType", DefaultCarConfig.Main.EngineType);
		ACarConfig.Main.ScaleBrakesWithRims = mINI_ReadInteger(GeneralINI, "Main", "ScaleBrakesWithRims", DefaultCarConfig.Main.ScaleBrakesWithRims);
		ACarConfig.Main.ListAttachmentsUnderParts = mINI_ReadInteger(GeneralINI, "Main", "ListAttachmentsUnderParts", DefaultCarConfig.Main.ListAttachmentsUnderParts);

		// Category (also check Main for backwards compatibility)
		ACarConfig.Category.Parts = mINI_ReadInteger(CarINI, "Main", "Parts", DefaultCarConfig.Category.Parts) != 0;
		ACarConfig.Category.Performance = mINI_ReadInteger(CarINI, "Main", "Performance", DefaultCarConfig.Category.Performance) != 0;
		ACarConfig.Category.Visual = mINI_ReadInteger(CarINI, "Main", "Visual", DefaultCarConfig.Category.Visual) != 0;

		ACarConfig.Category.Parts = mINI_ReadInteger(CarINI, "Category", "Parts", ACarConfig.Category.Parts) != 0;
		ACarConfig.Category.Performance = mINI_ReadInteger(CarINI, "Category", "Performance", ACarConfig.Category.Performance) != 0;
		ACarConfig.Category.Visual = mINI_ReadInteger(CarINI, "Category", "Visual", ACarConfig.Category.Visual) != 0;

		// Textures
		ACarConfig.Textures.HeadlightOff = mINI_ReadInteger(CarINI, "Textures", "HeadlightOff", DefaultCarConfig.Textures.HeadlightOff) != 0;
		ACarConfig.Textures.DamageLights = mINI_ReadInteger(CarINI, "Textures", "DamageLights", DefaultCarConfig.Textures.DamageLights) != 0;
		ACarConfig.Textures.CentreBrake = mINI_ReadInteger(CarINI, "Textures", "CentreBrake", DefaultCarConfig.Textures.CentreBrake) != 0;
		ACarConfig.Textures.Reverse = mINI_ReadInteger(CarINI, "Textures", "Reverse", DefaultCarConfig.Textures.Reverse) != 0;
		ACarConfig.Textures.BrakelightOnfInGame = mINI_ReadInteger(CarINI, "Textures", "BrakelightOnfInGame", DefaultCarConfig.Textures.BrakelightOnfInGame) != 0;
		ACarConfig.Textures.TireInnerMask = mINI_ReadInteger(CarINI, "Textures", "TireInnerMask", DefaultCarConfig.Textures.TireInnerMask) != 0;

		// Parts
		ACarConfig.Parts.BodyKits = mINI_ReadInteger(CarINI, "Parts", "BodyKits", DefaultCarConfig.Parts.BodyKits) != 0;
		ACarConfig.Parts.Spoilers = mINI_ReadInteger(CarINI, "Parts", "Spoilers", DefaultCarConfig.Parts.Spoilers) != 0;
		ACarConfig.Parts.Rims = mINI_ReadInteger(CarINI, "Parts", "Rims", DefaultCarConfig.Parts.Rims) != 0;
		ACarConfig.Parts.RimsCustom = mINI_ReadInteger(CarINI, "Parts", "RimsCustom", DefaultCarConfig.Parts.RimsCustom) != 0;
		ACarConfig.Parts.Hoods = mINI_ReadInteger(CarINI, "Parts", "Hoods", DefaultCarConfig.Parts.Hoods) != 0;
		ACarConfig.Parts.RoofScoops = mINI_ReadInteger(CarINI, "Parts", "RoofScoops", DefaultCarConfig.Parts.RoofScoops) != 0;
		ACarConfig.Parts.Interior = mINI_ReadInteger(CarINI, "Parts", "Interior", DefaultCarConfig.Parts.Interior) != 0;
		ACarConfig.Parts.Roof = mINI_ReadInteger(CarINI, "Parts", "Roof", DefaultCarConfig.Parts.Roof) != 0;
		ACarConfig.Parts.Brakes = mINI_ReadInteger(CarINI, "Parts", "Brakes", DefaultCarConfig.Parts.Brakes) != 0;
		ACarConfig.Parts.Headlights = mINI_ReadInteger(CarINI, "Parts", "Headlights", DefaultCarConfig.Parts.Headlights) != 0;
		ACarConfig.Parts.Taillights = mINI_ReadInteger(CarINI, "Parts", "Taillights", DefaultCarConfig.Parts.Taillights) != 0;
		ACarConfig.Parts.Mirrors = mINI_ReadInteger(CarINI, "Parts", "Mirrors", DefaultCarConfig.Parts.Mirrors) != 0;
		ACarConfig.Parts.Attachments = mINI_ReadInteger(CarINI, "Parts", "Attachments", DefaultCarConfig.Parts.Attachments) % 11;

		// Performance
		ACarConfig.Performance.Engine = mINI_ReadInteger(CarINI, "Performance", "Engine", DefaultCarConfig.Performance.Engine) != 0;
		ACarConfig.Performance.Transmission = mINI_ReadInteger(CarINI, "Performance", "Transmission", DefaultCarConfig.Performance.Transmission) != 0;
		ACarConfig.Performance.Chassis = mINI_ReadInteger(CarINI, "Performance", "Chassis", DefaultCarConfig.Performance.Chassis) != 0;
		ACarConfig.Performance.Nitrous = mINI_ReadInteger(CarINI, "Performance", "Nitrous", DefaultCarConfig.Performance.Nitrous) != 0;
		ACarConfig.Performance.Tires = mINI_ReadInteger(CarINI, "Performance", "Tires", DefaultCarConfig.Performance.Tires) != 0;
		ACarConfig.Performance.Brakes = mINI_ReadInteger(CarINI, "Performance", "Brakes", DefaultCarConfig.Performance.Brakes) != 0;
		ACarConfig.Performance.Induction = mINI_ReadInteger(CarINI, "Performance", "Induction", DefaultCarConfig.Performance.Induction) != 0;

		// Visual
		ACarConfig.Visual.Paint = mINI_ReadInteger(CarINI, "Visual", "Paint", DefaultCarConfig.Visual.Paint) != 0;
		ACarConfig.Visual.PaintCustom = mINI_ReadInteger(CarINI, "Visual", "PaintCustom", DefaultCarConfig.Visual.PaintCustom) != 0;
		ACarConfig.Visual.Vinyls = mINI_ReadInteger(CarINI, "Visual", "Vinyls", DefaultCarConfig.Visual.Vinyls) != 0;
		ACarConfig.Visual.VinylsCustom = mINI_ReadInteger(CarINI, "Visual", "VinylsCustom", DefaultCarConfig.Visual.VinylsCustom) != 0;
		ACarConfig.Visual.RimPaint = mINI_ReadInteger(CarINI, "Visual", "RimPaint", DefaultCarConfig.Visual.RimPaint) != 0;
		ACarConfig.Visual.WindowTint = mINI_ReadInteger(CarINI, "Visual", "WindowTint", DefaultCarConfig.Visual.WindowTint) != 0;
		ACarConfig.Visual.Decals = mINI_ReadInteger(CarINI, "Visual", "Decals", DefaultCarConfig.Visual.Decals) != 0;
		ACarConfig.Visual.DecalsWindshield = mINI_ReadInteger(CarINI, "Visual", "DecalsWindshield", DefaultCarConfig.Visual.DecalsWindshield) != 0;
		ACarConfig.Visual.DecalsRearWindow = mINI_ReadInteger(CarINI, "Visual", "DecalsRearWindow", DefaultCarConfig.Visual.DecalsRearWindow) != 0;
		ACarConfig.Visual.DecalsLeftDoor = mINI_ReadInteger(CarINI, "Visual", "DecalsLeftDoor", DefaultCarConfig.Visual.DecalsLeftDoor) != 0;
		ACarConfig.Visual.DecalsRightDoor = mINI_ReadInteger(CarINI, "Visual", "DecalsRightDoor", DefaultCarConfig.Visual.DecalsRightDoor) != 0;
		ACarConfig.Visual.DecalsLeftQuarter = mINI_ReadInteger(CarINI, "Visual", "DecalsLeftQuarter", DefaultCarConfig.Visual.DecalsLeftQuarter) != 0;
		ACarConfig.Visual.DecalsRightQuarter = mINI_ReadInteger(CarINI, "Visual", "DecalsRightQuarter", DefaultCarConfig.Visual.DecalsRightQuarter) != 0;
		ACarConfig.Visual.Numbers = mINI_ReadInteger(CarINI, "Visual", "Numbers", DefaultCarConfig.Visual.Numbers) != 0;
		ACarConfig.Visual.CustomGauges = mINI_ReadInteger(CarINI, "Visual", "CustomGauges", DefaultCarConfig.Visual.CustomGauges) != 0;
		ACarConfig.Visual.Driver = mINI_ReadInteger(CarINI, "Visual", "Driver", DefaultCarConfig.Visual.Driver) != 0;
		ACarConfig.Visual.LicensePlate = mINI_ReadInteger(CarINI, "Visual", "LicensePlate", DefaultCarConfig.Visual.LicensePlate) != 0;
		ACarConfig.Visual.Tires = mINI_ReadInteger(CarINI, "Visual", "Tires", DefaultCarConfig.Visual.Tires) != 0;
		ACarConfig.Visual.Neon = mINI_ReadInteger(CarINI, "Visual", "Neon", DefaultCarConfig.Visual.Neon) != 0;

		// Icons
		ACarConfig.Icons.Parts = mINI_ReadHash(CarINI, "Icons", "Parts", DefaultCarConfig.Icons.Parts);
		ACarConfig.Icons.PartsBodyKits = mINI_ReadHash(CarINI, "Icons", "PartsBodykits", DefaultCarConfig.Icons.PartsBodyKits);
		ACarConfig.Icons.PartsSpoilers = mINI_ReadHash(CarINI, "Icons", "PartsSpoilers", DefaultCarConfig.Icons.PartsSpoilers);
		ACarConfig.Icons.PartsSpoilersCF = mINI_ReadHash(CarINI, "Icons", "PartsSpoilersCF", DefaultCarConfig.Icons.PartsSpoilersCF);
		ACarConfig.Icons.PartsRims = mINI_ReadHash(CarINI, "Icons", "PartsRims", DefaultCarConfig.Icons.PartsRims);
		ACarConfig.Icons.PartsRimsCustom = mINI_ReadHash(CarINI, "Icons", "PartsRimsCustom", DefaultCarConfig.Icons.PartsRimsCustom);
		ACarConfig.Icons.PartsHoods = mINI_ReadHash(CarINI, "Icons", "PartsHoods", DefaultCarConfig.Icons.PartsHoods);
		ACarConfig.Icons.PartsHoodsCF = mINI_ReadHash(CarINI, "Icons", "PartsHoodsCF", DefaultCarConfig.Icons.PartsHoodsCF);
		ACarConfig.Icons.PartsRoofScoops = mINI_ReadHash(CarINI, "Icons", "PartsRoofScoops", DefaultCarConfig.Icons.PartsRoofScoops);
		ACarConfig.Icons.PartsRoofScoopsCF = mINI_ReadHash(CarINI, "Icons", "PartsRoofScoopsCF", DefaultCarConfig.Icons.PartsRoofScoopsCF);
		ACarConfig.Icons.PartsInterior = mINI_ReadHash(CarINI, "Icons", "PartsInterior", DefaultCarConfig.Icons.PartsInterior);
		ACarConfig.Icons.PartsRoof = mINI_ReadHash(CarINI, "Icons", "PartsRoof", DefaultCarConfig.Icons.PartsRoof);
		ACarConfig.Icons.PartsBrakes = mINI_ReadHash(CarINI, "Icons", "PartsBrakes", DefaultCarConfig.Icons.PartsBrakes);
		ACarConfig.Icons.PartsHeadlights = mINI_ReadHash(CarINI, "Icons", "PartsHeadlights", DefaultCarConfig.Icons.PartsHeadlights);
		ACarConfig.Icons.PartsTaillights = mINI_ReadHash(CarINI, "Icons", "PartsTaillights", DefaultCarConfig.Icons.PartsTaillights);
		ACarConfig.Icons.PartsMirrors = mINI_ReadHash(CarINI, "Icons", "PartsMirrors", DefaultCarConfig.Icons.PartsMirrors);
		ACarConfig.Icons.PartsAttachments = mINI_ReadHash(CarINI, "Icons", "PartsAttachments", DefaultCarConfig.Icons.PartsAttachments);
		ACarConfig.Icons.PartsAttachment0 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment0", DefaultCarConfig.Icons.PartsAttachment0);
		ACarConfig.Icons.PartsAttachment1 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment1", DefaultCarConfig.Icons.PartsAttachment1);
		ACarConfig.Icons.PartsAttachment2 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment2", DefaultCarConfig.Icons.PartsAttachment2);
		ACarConfig.Icons.PartsAttachment3 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment3", DefaultCarConfig.Icons.PartsAttachment3);
		ACarConfig.Icons.PartsAttachment4 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment4", DefaultCarConfig.Icons.PartsAttachment4);
		ACarConfig.Icons.PartsAttachment5 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment5", DefaultCarConfig.Icons.PartsAttachment5);
		ACarConfig.Icons.PartsAttachment6 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment6", DefaultCarConfig.Icons.PartsAttachment6);
		ACarConfig.Icons.PartsAttachment7 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment7", DefaultCarConfig.Icons.PartsAttachment7);
		ACarConfig.Icons.PartsAttachment8 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment8", DefaultCarConfig.Icons.PartsAttachment8);
		ACarConfig.Icons.PartsAttachment9 = mINI_ReadHash(CarINI, "Icons", "PartsAttachment9", DefaultCarConfig.Icons.PartsAttachment9);
		ACarConfig.Icons.Performance = mINI_ReadHash(CarINI, "Icons", "Performance", DefaultCarConfig.Icons.Performance);
		ACarConfig.Icons.PerformanceEngine = mINI_ReadHash(CarINI, "Icons", "PerformanceEngine", DefaultCarConfig.Icons.PerformanceEngine);
		ACarConfig.Icons.PerformanceTransmission = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmission", DefaultCarConfig.Icons.PerformanceTransmission);
		ACarConfig.Icons.PerformanceChassis = mINI_ReadHash(CarINI, "Icons", "PerformanceChassis", DefaultCarConfig.Icons.PerformanceChassis);
		ACarConfig.Icons.PerformanceNitrous = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrous", DefaultCarConfig.Icons.PerformanceNitrous);
		ACarConfig.Icons.PerformanceTires = mINI_ReadHash(CarINI, "Icons", "PerformanceTires", DefaultCarConfig.Icons.PerformanceTires);
		ACarConfig.Icons.PerformanceBrakes = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakes", DefaultCarConfig.Icons.PerformanceBrakes);
		ACarConfig.Icons.PerformanceTurbo = mINI_ReadHash(CarINI, "Icons", "PerformanceTurbo", DefaultCarConfig.Icons.PerformanceTurbo);
		ACarConfig.Icons.PerformanceSupercharger = mINI_ReadHash(CarINI, "Icons", "PerformanceSupercharger", DefaultCarConfig.Icons.PerformanceSupercharger);
		ACarConfig.Icons.Visual = mINI_ReadHash(CarINI, "Icons", "Visual", DefaultCarConfig.Icons.Visual);
		ACarConfig.Icons.VisualPaint = mINI_ReadHash(CarINI, "Icons", "VisualPaint", DefaultCarConfig.Icons.VisualPaint);
		ACarConfig.Icons.VisualVinyls = mINI_ReadHash(CarINI, "Icons", "VisualVinyls", DefaultCarConfig.Icons.VisualVinyls);
		ACarConfig.Icons.VisualVinylsCustom = mINI_ReadHash(CarINI, "Icons", "VisualVinylsCustom", DefaultCarConfig.Icons.VisualVinylsCustom);
		ACarConfig.Icons.VisualRimPaint = mINI_ReadHash(CarINI, "Icons", "VisualRimPaint", DefaultCarConfig.Icons.VisualRimPaint);
		ACarConfig.Icons.VisualWindowTint = mINI_ReadHash(CarINI, "Icons", "VisualWindowTint", DefaultCarConfig.Icons.VisualWindowTint);
		ACarConfig.Icons.VisualDecals = mINI_ReadHash(CarINI, "Icons", "VisualDecals", DefaultCarConfig.Icons.VisualDecals);
		ACarConfig.Icons.VisualDecalsWindshield = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield", DefaultCarConfig.Icons.VisualDecalsWindshield);
		ACarConfig.Icons.VisualDecalsWindshield1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield1", DefaultCarConfig.Icons.VisualDecalsWindshield1);
		ACarConfig.Icons.VisualDecalsWindshield2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield2", DefaultCarConfig.Icons.VisualDecalsWindshield2);
		ACarConfig.Icons.VisualDecalsWindshield3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield3", DefaultCarConfig.Icons.VisualDecalsWindshield3);
		ACarConfig.Icons.VisualDecalsWindshield4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield4", DefaultCarConfig.Icons.VisualDecalsWindshield4);
		ACarConfig.Icons.VisualDecalsWindshield5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield5", DefaultCarConfig.Icons.VisualDecalsWindshield5);
		ACarConfig.Icons.VisualDecalsWindshield6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield6", DefaultCarConfig.Icons.VisualDecalsWindshield6);
		ACarConfig.Icons.VisualDecalsWindshield7 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield7", DefaultCarConfig.Icons.VisualDecalsWindshield7);
		ACarConfig.Icons.VisualDecalsWindshield8 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsWindshield8", DefaultCarConfig.Icons.VisualDecalsWindshield8);
		ACarConfig.Icons.VisualDecalsRearWindow = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow", DefaultCarConfig.Icons.VisualDecalsRearWindow);
		ACarConfig.Icons.VisualDecalsRearWindow1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow1", DefaultCarConfig.Icons.VisualDecalsRearWindow1);
		ACarConfig.Icons.VisualDecalsRearWindow2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow2", DefaultCarConfig.Icons.VisualDecalsRearWindow2);
		ACarConfig.Icons.VisualDecalsRearWindow3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow3", DefaultCarConfig.Icons.VisualDecalsRearWindow3);
		ACarConfig.Icons.VisualDecalsRearWindow4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow4", DefaultCarConfig.Icons.VisualDecalsRearWindow4);
		ACarConfig.Icons.VisualDecalsRearWindow5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow5", DefaultCarConfig.Icons.VisualDecalsRearWindow5);
		ACarConfig.Icons.VisualDecalsRearWindow6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow6", DefaultCarConfig.Icons.VisualDecalsRearWindow6);
		ACarConfig.Icons.VisualDecalsRearWindow7 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow7", DefaultCarConfig.Icons.VisualDecalsRearWindow7);
		ACarConfig.Icons.VisualDecalsRearWindow8 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRearWindow8", DefaultCarConfig.Icons.VisualDecalsRearWindow8);
		ACarConfig.Icons.VisualDecalsLeftDoor = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor", DefaultCarConfig.Icons.VisualDecalsLeftDoor);
		ACarConfig.Icons.VisualDecalsLeftDoor1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor1", DefaultCarConfig.Icons.VisualDecalsLeftDoor1);
		ACarConfig.Icons.VisualDecalsLeftDoor2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor2", DefaultCarConfig.Icons.VisualDecalsLeftDoor2);
		ACarConfig.Icons.VisualDecalsLeftDoor3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor3", DefaultCarConfig.Icons.VisualDecalsLeftDoor3);
		ACarConfig.Icons.VisualDecalsLeftDoor4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor4", DefaultCarConfig.Icons.VisualDecalsLeftDoor4);
		ACarConfig.Icons.VisualDecalsLeftDoor5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor5", DefaultCarConfig.Icons.VisualDecalsLeftDoor5);
		ACarConfig.Icons.VisualDecalsLeftDoor6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftDoor6", DefaultCarConfig.Icons.VisualDecalsLeftDoor6);
		ACarConfig.Icons.VisualDecalsRightDoor = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor", DefaultCarConfig.Icons.VisualDecalsRightDoor);
		ACarConfig.Icons.VisualDecalsRightDoor1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor1", DefaultCarConfig.Icons.VisualDecalsRightDoor1);
		ACarConfig.Icons.VisualDecalsRightDoor2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor2", DefaultCarConfig.Icons.VisualDecalsRightDoor2);
		ACarConfig.Icons.VisualDecalsRightDoor3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor3", DefaultCarConfig.Icons.VisualDecalsRightDoor3);
		ACarConfig.Icons.VisualDecalsRightDoor4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor4", DefaultCarConfig.Icons.VisualDecalsRightDoor4);
		ACarConfig.Icons.VisualDecalsRightDoor5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor5", DefaultCarConfig.Icons.VisualDecalsRightDoor5);
		ACarConfig.Icons.VisualDecalsRightDoor6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightDoor6", DefaultCarConfig.Icons.VisualDecalsRightDoor6);
		ACarConfig.Icons.VisualDecalsLeftQuarter = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter", DefaultCarConfig.Icons.VisualDecalsLeftQuarter);
		ACarConfig.Icons.VisualDecalsLeftQuarter1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter1", DefaultCarConfig.Icons.VisualDecalsLeftQuarter1);
		ACarConfig.Icons.VisualDecalsLeftQuarter2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter2", DefaultCarConfig.Icons.VisualDecalsLeftQuarter2);
		ACarConfig.Icons.VisualDecalsLeftQuarter3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter3", DefaultCarConfig.Icons.VisualDecalsLeftQuarter3);
		ACarConfig.Icons.VisualDecalsLeftQuarter4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter4", DefaultCarConfig.Icons.VisualDecalsLeftQuarter4);
		ACarConfig.Icons.VisualDecalsLeftQuarter5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter5", DefaultCarConfig.Icons.VisualDecalsLeftQuarter5);
		ACarConfig.Icons.VisualDecalsLeftQuarter6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter6", DefaultCarConfig.Icons.VisualDecalsLeftQuarter6);
		ACarConfig.Icons.VisualDecalsLeftQuarter7 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter7", DefaultCarConfig.Icons.VisualDecalsLeftQuarter7);
		ACarConfig.Icons.VisualDecalsLeftQuarter8 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsLeftQuarter8", DefaultCarConfig.Icons.VisualDecalsLeftQuarter8);
		ACarConfig.Icons.VisualDecalsRightQuarter = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter", DefaultCarConfig.Icons.VisualDecalsRightQuarter);
		ACarConfig.Icons.VisualDecalsRightQuarter1 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter1", DefaultCarConfig.Icons.VisualDecalsRightQuarter1);
		ACarConfig.Icons.VisualDecalsRightQuarter2 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter2", DefaultCarConfig.Icons.VisualDecalsRightQuarter2);
		ACarConfig.Icons.VisualDecalsRightQuarter3 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter3", DefaultCarConfig.Icons.VisualDecalsRightQuarter3);
		ACarConfig.Icons.VisualDecalsRightQuarter4 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter4", DefaultCarConfig.Icons.VisualDecalsRightQuarter4);
		ACarConfig.Icons.VisualDecalsRightQuarter5 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter5", DefaultCarConfig.Icons.VisualDecalsRightQuarter5);
		ACarConfig.Icons.VisualDecalsRightQuarter6 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter6", DefaultCarConfig.Icons.VisualDecalsRightQuarter6);
		ACarConfig.Icons.VisualDecalsRightQuarter7 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter7", DefaultCarConfig.Icons.VisualDecalsRightQuarter7);
		ACarConfig.Icons.VisualDecalsRightQuarter8 = mINI_ReadHash(CarINI, "Icons", "VisualDecalsRightQuarter8", DefaultCarConfig.Icons.VisualDecalsRightQuarter8);
		ACarConfig.Icons.VisualNumbers = mINI_ReadHash(CarINI, "Icons", "VisualNumbers", DefaultCarConfig.Icons.VisualNumbers);
		ACarConfig.Icons.VisualCustomGauges = mINI_ReadHash(CarINI, "Icons", "VisualCustomGauges", DefaultCarConfig.Icons.VisualCustomGauges);
		ACarConfig.Icons.VisualDriver = mINI_ReadHash(CarINI, "Icons", "VisualDriver", DefaultCarConfig.Icons.VisualDriver);
		ACarConfig.Icons.VisualLicensePlate = mINI_ReadHash(CarINI, "Icons", "VisualLicensePlate", DefaultCarConfig.Icons.VisualLicensePlate);
		ACarConfig.Icons.VisualTires = mINI_ReadHash(CarINI, "Icons", "VisualTires", DefaultCarConfig.Icons.VisualTires);
		ACarConfig.Icons.VisualNeon = mINI_ReadHash(CarINI, "Icons", "VisualNeon", DefaultCarConfig.Icons.VisualNeon);
		ACarConfig.Icons.BackroomParts = mINI_ReadHash(CarINI, "Icons", "BackroomParts", DefaultCarConfig.Icons.BackroomParts);
		ACarConfig.Icons.BackroomPartsBodyKits = mINI_ReadHash(CarINI, "Icons", "BackroomPartsBodyKits", DefaultCarConfig.Icons.BackroomPartsBodyKits);
		ACarConfig.Icons.BackroomPartsSpoilers = mINI_ReadHash(CarINI, "Icons", "BackroomPartsSpoilers", DefaultCarConfig.Icons.BackroomPartsSpoilers);
		ACarConfig.Icons.BackroomPartsSpoilersCF = mINI_ReadHash(CarINI, "Icons", "BackroomPartsSpoilersCF", DefaultCarConfig.Icons.BackroomPartsSpoilersCF);
		ACarConfig.Icons.BackroomPartsRims = mINI_ReadHash(CarINI, "Icons", "BackroomPartsRims", DefaultCarConfig.Icons.BackroomPartsRims);
		ACarConfig.Icons.BackroomPartsHoods = mINI_ReadHash(CarINI, "Icons", "BackroomPartsHoods", DefaultCarConfig.Icons.BackroomPartsHoods);
		ACarConfig.Icons.BackroomPartsHoodsCF = mINI_ReadHash(CarINI, "Icons", "BackroomPartsHoodsCF", DefaultCarConfig.Icons.BackroomPartsHoodsCF);
		ACarConfig.Icons.BackroomPartsRoofScoops = mINI_ReadHash(CarINI, "Icons", "BackroomPartsRoofScoops", DefaultCarConfig.Icons.BackroomPartsRoofScoops);
		ACarConfig.Icons.BackroomPartsRoofScoopsCF = mINI_ReadHash(CarINI, "Icons", "BackroomPartsRoofScoopsCF", DefaultCarConfig.Icons.BackroomPartsRoofScoopsCF);
		ACarConfig.Icons.BackroomPerformance = mINI_ReadHash(CarINI, "Icons", "BackroomPerformance", DefaultCarConfig.Icons.BackroomPerformance);
		ACarConfig.Icons.BackroomPerformanceEngine = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceEngine", DefaultCarConfig.Icons.BackroomPerformanceEngine);
		ACarConfig.Icons.BackroomPerformanceTransmission = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceTransmission", DefaultCarConfig.Icons.BackroomPerformanceTransmission);
		ACarConfig.Icons.BackroomPerformanceChassis = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceChassis", DefaultCarConfig.Icons.BackroomPerformanceChassis);
		ACarConfig.Icons.BackroomPerformanceNitrous = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceNitrous", DefaultCarConfig.Icons.BackroomPerformanceNitrous);
		ACarConfig.Icons.BackroomPerformanceTires = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceTires", DefaultCarConfig.Icons.BackroomPerformanceTires);
		ACarConfig.Icons.BackroomPerformanceBrakes = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceBrakes", DefaultCarConfig.Icons.BackroomPerformanceBrakes);
		ACarConfig.Icons.BackroomPerformanceTurbo = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceTurbo", DefaultCarConfig.Icons.BackroomPerformanceTurbo);
		ACarConfig.Icons.BackroomPerformanceSupercharger = mINI_ReadHash(CarINI, "Icons", "BackroomPerformanceSupercharger", DefaultCarConfig.Icons.BackroomPerformanceSupercharger);
		ACarConfig.Icons.BackroomVisual = mINI_ReadHash(CarINI, "Icons", "BackroomVisual", DefaultCarConfig.Icons.BackroomVisual);
		ACarConfig.Icons.BackroomVisualPaint = mINI_ReadHash(CarINI, "Icons", "BackroomVisualPaint", DefaultCarConfig.Icons.BackroomVisualPaint);
		ACarConfig.Icons.BackroomVisualVinyls = mINI_ReadHash(CarINI, "Icons", "BackroomVisualVinyls", DefaultCarConfig.Icons.BackroomVisualVinyls);
		ACarConfig.Icons.BackroomVisualDecals = mINI_ReadHash(CarINI, "Icons", "BackroomVisualDecals", DefaultCarConfig.Icons.BackroomVisualDecals);
		ACarConfig.Icons.BackroomVisualCustomGauges = mINI_ReadHash(CarINI, "Icons", "BackroomVisualCustomGauges", DefaultCarConfig.Icons.BackroomVisualCustomGauges);
		ACarConfig.Icons.PerformanceEngineStock = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineStock", DefaultCarConfig.Icons.PerformanceEngineStock);
		ACarConfig.Icons.PerformanceEngineStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineStreet", DefaultCarConfig.Icons.PerformanceEngineStreet);
		ACarConfig.Icons.PerformanceEngineSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineSuperStreet", DefaultCarConfig.Icons.PerformanceEngineSuperStreet);
		ACarConfig.Icons.PerformanceEngineRace = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineRace", DefaultCarConfig.Icons.PerformanceEngineRace);
		ACarConfig.Icons.PerformanceEnginePro = mINI_ReadHash(CarINI, "Icons", "PerformanceEnginePro", DefaultCarConfig.Icons.PerformanceEnginePro);
		ACarConfig.Icons.PerformanceEngineSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineSuperPro", DefaultCarConfig.Icons.PerformanceEngineSuperPro);
		ACarConfig.Icons.PerformanceEngineUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineUltimate", DefaultCarConfig.Icons.PerformanceEngineUltimate);
		ACarConfig.Icons.PerformanceEngineJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineJunkman", DefaultCarConfig.Icons.PerformanceEngineJunkman);
		ACarConfig.Icons.PerformanceTransmissionStock = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionStock", DefaultCarConfig.Icons.PerformanceTransmissionStock);
		ACarConfig.Icons.PerformanceTransmissionStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionStreet", DefaultCarConfig.Icons.PerformanceTransmissionStreet);
		ACarConfig.Icons.PerformanceTransmissionSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionSuperStreet", DefaultCarConfig.Icons.PerformanceTransmissionSuperStreet);
		ACarConfig.Icons.PerformanceTransmissionRace = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionRace", DefaultCarConfig.Icons.PerformanceTransmissionRace);
		ACarConfig.Icons.PerformanceTransmissionPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionPro", DefaultCarConfig.Icons.PerformanceTransmissionPro);
		ACarConfig.Icons.PerformanceTransmissionSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionSuperPro", DefaultCarConfig.Icons.PerformanceTransmissionSuperPro);
		ACarConfig.Icons.PerformanceTransmissionUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionUltimate", DefaultCarConfig.Icons.PerformanceTransmissionUltimate);
		ACarConfig.Icons.PerformanceTransmissionJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionJunkman", DefaultCarConfig.Icons.PerformanceTransmissionJunkman);
		ACarConfig.Icons.PerformanceChassisStock = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisStock", DefaultCarConfig.Icons.PerformanceChassisStock);
		ACarConfig.Icons.PerformanceChassisStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisStreet", DefaultCarConfig.Icons.PerformanceChassisStreet);
		ACarConfig.Icons.PerformanceChassisSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisSuperStreet", DefaultCarConfig.Icons.PerformanceChassisSuperStreet);
		ACarConfig.Icons.PerformanceChassisRace = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisRace", DefaultCarConfig.Icons.PerformanceChassisRace);
		ACarConfig.Icons.PerformanceChassisPro = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisPro", DefaultCarConfig.Icons.PerformanceChassisPro);
		ACarConfig.Icons.PerformanceChassisSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisSuperPro", DefaultCarConfig.Icons.PerformanceChassisSuperPro);
		ACarConfig.Icons.PerformanceChassisUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisUltimate", DefaultCarConfig.Icons.PerformanceChassisUltimate);
		ACarConfig.Icons.PerformanceChassisJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisJunkman", DefaultCarConfig.Icons.PerformanceChassisJunkman);
		ACarConfig.Icons.PerformanceNitrousStock = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousStock", DefaultCarConfig.Icons.PerformanceNitrousStock);
		ACarConfig.Icons.PerformanceNitrousStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousStreet", DefaultCarConfig.Icons.PerformanceNitrousStreet);
		ACarConfig.Icons.PerformanceNitrousSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousSuperStreet", DefaultCarConfig.Icons.PerformanceNitrousSuperStreet);
		ACarConfig.Icons.PerformanceNitrousRace = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousRace", DefaultCarConfig.Icons.PerformanceNitrousRace);
		ACarConfig.Icons.PerformanceNitrousPro = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousPro", DefaultCarConfig.Icons.PerformanceNitrousPro);
		ACarConfig.Icons.PerformanceNitrousSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousSuperPro", DefaultCarConfig.Icons.PerformanceNitrousSuperPro);
		ACarConfig.Icons.PerformanceNitrousUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousUltimate", DefaultCarConfig.Icons.PerformanceNitrousUltimate);
		ACarConfig.Icons.PerformanceNitrousJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousJunkman", DefaultCarConfig.Icons.PerformanceNitrousJunkman);
		ACarConfig.Icons.PerformanceTiresStock = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresStock", DefaultCarConfig.Icons.PerformanceTiresStock);
		ACarConfig.Icons.PerformanceTiresStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresStreet", DefaultCarConfig.Icons.PerformanceTiresStreet);
		ACarConfig.Icons.PerformanceTiresSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresSuperStreet", DefaultCarConfig.Icons.PerformanceTiresSuperStreet);
		ACarConfig.Icons.PerformanceTiresRace = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresRace", DefaultCarConfig.Icons.PerformanceTiresRace);
		ACarConfig.Icons.PerformanceTiresPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresPro", DefaultCarConfig.Icons.PerformanceTiresPro);
		ACarConfig.Icons.PerformanceTiresSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresSuperPro", DefaultCarConfig.Icons.PerformanceTiresSuperPro);
		ACarConfig.Icons.PerformanceTiresUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresUltimate", DefaultCarConfig.Icons.PerformanceTiresUltimate);
		ACarConfig.Icons.PerformanceTiresJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresJunkman", DefaultCarConfig.Icons.PerformanceTiresJunkman);
		ACarConfig.Icons.PerformanceBrakesStock = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesStock", DefaultCarConfig.Icons.PerformanceBrakesStock);
		ACarConfig.Icons.PerformanceBrakesStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesStreet", DefaultCarConfig.Icons.PerformanceBrakesStreet);
		ACarConfig.Icons.PerformanceBrakesSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesSuperStreet", DefaultCarConfig.Icons.PerformanceBrakesSuperStreet);
		ACarConfig.Icons.PerformanceBrakesRace = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesRace", DefaultCarConfig.Icons.PerformanceBrakesRace);
		ACarConfig.Icons.PerformanceBrakesPro = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesPro", DefaultCarConfig.Icons.PerformanceBrakesPro);
		ACarConfig.Icons.PerformanceBrakesSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesSuperPro", DefaultCarConfig.Icons.PerformanceBrakesSuperPro);
		ACarConfig.Icons.PerformanceBrakesUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesUltimate", DefaultCarConfig.Icons.PerformanceBrakesUltimate);
		ACarConfig.Icons.PerformanceBrakesJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesJunkman", DefaultCarConfig.Icons.PerformanceBrakesJunkman);
		ACarConfig.Icons.PerformanceTurboStock = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboStock", DefaultCarConfig.Icons.PerformanceTurboStock);
		ACarConfig.Icons.PerformanceTurboStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboStreet", DefaultCarConfig.Icons.PerformanceTurboStreet);
		ACarConfig.Icons.PerformanceTurboSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboSuperStreet", DefaultCarConfig.Icons.PerformanceTurboSuperStreet);
		ACarConfig.Icons.PerformanceTurboRace = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboRace", DefaultCarConfig.Icons.PerformanceTurboRace);
		ACarConfig.Icons.PerformanceTurboPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboPro", DefaultCarConfig.Icons.PerformanceTurboPro);
		ACarConfig.Icons.PerformanceTurboSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboSuperPro", DefaultCarConfig.Icons.PerformanceTurboSuperPro);
		ACarConfig.Icons.PerformanceTurboUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboUltimate", DefaultCarConfig.Icons.PerformanceTurboUltimate);
		ACarConfig.Icons.PerformanceTurboJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboJunkman", DefaultCarConfig.Icons.PerformanceTurboJunkman);
		ACarConfig.Icons.PerformanceSuperchargerStock = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerStock", DefaultCarConfig.Icons.PerformanceSuperchargerStock);
		ACarConfig.Icons.PerformanceSuperchargerStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerStreet", DefaultCarConfig.Icons.PerformanceSuperchargerStreet);
		ACarConfig.Icons.PerformanceSuperchargerSuperStreet = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerSuperStreet", DefaultCarConfig.Icons.PerformanceSuperchargerSuperStreet);
		ACarConfig.Icons.PerformanceSuperchargerRace = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerRace", DefaultCarConfig.Icons.PerformanceSuperchargerRace);
		ACarConfig.Icons.PerformanceSuperchargerPro = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerPro", DefaultCarConfig.Icons.PerformanceSuperchargerPro);
		ACarConfig.Icons.PerformanceSuperchargerSuperPro = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerSuperPro", DefaultCarConfig.Icons.PerformanceSuperchargerSuperPro);
		ACarConfig.Icons.PerformanceSuperchargerUltimate = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerUltimate", DefaultCarConfig.Icons.PerformanceSuperchargerUltimate);
		ACarConfig.Icons.PerformanceSuperchargerJunkman = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerJunkman", DefaultCarConfig.Icons.PerformanceSuperchargerJunkman);
		ACarConfig.Icons.PerformanceEngineLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel1Item1", DefaultCarConfig.Icons.PerformanceEngineLevel1Item1);
		ACarConfig.Icons.PerformanceEngineLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel1Item2", DefaultCarConfig.Icons.PerformanceEngineLevel1Item2);
		ACarConfig.Icons.PerformanceEngineLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel1Item3", DefaultCarConfig.Icons.PerformanceEngineLevel1Item3);
		ACarConfig.Icons.PerformanceEngineLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel2Item1", DefaultCarConfig.Icons.PerformanceEngineLevel2Item1);
		ACarConfig.Icons.PerformanceEngineLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel2Item2", DefaultCarConfig.Icons.PerformanceEngineLevel2Item2);
		ACarConfig.Icons.PerformanceEngineLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel2Item3", DefaultCarConfig.Icons.PerformanceEngineLevel2Item3);
		ACarConfig.Icons.PerformanceEngineLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel3Item1", DefaultCarConfig.Icons.PerformanceEngineLevel3Item1);
		ACarConfig.Icons.PerformanceEngineLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel3Item2", DefaultCarConfig.Icons.PerformanceEngineLevel3Item2);
		ACarConfig.Icons.PerformanceEngineLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel3Item3", DefaultCarConfig.Icons.PerformanceEngineLevel3Item3);
		ACarConfig.Icons.PerformanceEngineLevel4Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel4Item1", DefaultCarConfig.Icons.PerformanceEngineLevel4Item1);
		ACarConfig.Icons.PerformanceEngineLevel4Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel4Item2", DefaultCarConfig.Icons.PerformanceEngineLevel4Item2);
		ACarConfig.Icons.PerformanceEngineLevel4Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel4Item3", DefaultCarConfig.Icons.PerformanceEngineLevel4Item3);
		ACarConfig.Icons.PerformanceEngineLevel2Item1Rotary = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel2Item1Rotary", DefaultCarConfig.Icons.PerformanceEngineLevel2Item1Rotary);
		ACarConfig.Icons.PerformanceEngineLevel4Item1Rotary = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel4Item1Rotary", DefaultCarConfig.Icons.PerformanceEngineLevel4Item1Rotary);
		ACarConfig.Icons.PerformanceEngineLevel4Item3Castrol = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineLevel4Item3Castrol", DefaultCarConfig.Icons.PerformanceEngineLevel4Item3Castrol);
		ACarConfig.Icons.PerformanceEngineJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceEngineJunkmanItem", DefaultCarConfig.Icons.PerformanceEngineJunkmanItem);
		ACarConfig.Icons.PerformanceTransmissionLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel1Item1", DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item1);
		ACarConfig.Icons.PerformanceTransmissionLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel1Item2", DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item2);
		ACarConfig.Icons.PerformanceTransmissionLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel1Item3", DefaultCarConfig.Icons.PerformanceTransmissionLevel1Item3);
		ACarConfig.Icons.PerformanceTransmissionLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel2Item1", DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item1);
		ACarConfig.Icons.PerformanceTransmissionLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel2Item2", DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item2);
		ACarConfig.Icons.PerformanceTransmissionLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel2Item3", DefaultCarConfig.Icons.PerformanceTransmissionLevel2Item3);
		ACarConfig.Icons.PerformanceTransmissionLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel3Item1", DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item1);
		ACarConfig.Icons.PerformanceTransmissionLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel3Item2", DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item2);
		ACarConfig.Icons.PerformanceTransmissionLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel3Item3", DefaultCarConfig.Icons.PerformanceTransmissionLevel3Item3);
		ACarConfig.Icons.PerformanceTransmissionLevel4Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel4Item1", DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item1);
		ACarConfig.Icons.PerformanceTransmissionLevel4Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel4Item2", DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item2);
		ACarConfig.Icons.PerformanceTransmissionLevel4Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionLevel4Item3", DefaultCarConfig.Icons.PerformanceTransmissionLevel4Item3);
		ACarConfig.Icons.PerformanceTransmissionJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceTransmissionJunkmanItem", DefaultCarConfig.Icons.PerformanceTransmissionJunkmanItem);
		ACarConfig.Icons.PerformanceChassisLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel1Item1", DefaultCarConfig.Icons.PerformanceChassisLevel1Item1);
		ACarConfig.Icons.PerformanceChassisLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel1Item2", DefaultCarConfig.Icons.PerformanceChassisLevel1Item2);
		ACarConfig.Icons.PerformanceChassisLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel1Item3", DefaultCarConfig.Icons.PerformanceChassisLevel1Item3);
		ACarConfig.Icons.PerformanceChassisLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel2Item1", DefaultCarConfig.Icons.PerformanceChassisLevel2Item1);
		ACarConfig.Icons.PerformanceChassisLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel2Item2", DefaultCarConfig.Icons.PerformanceChassisLevel2Item2);
		ACarConfig.Icons.PerformanceChassisLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel2Item3", DefaultCarConfig.Icons.PerformanceChassisLevel2Item3);
		ACarConfig.Icons.PerformanceChassisLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel3Item1", DefaultCarConfig.Icons.PerformanceChassisLevel3Item1);
		ACarConfig.Icons.PerformanceChassisLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel3Item2", DefaultCarConfig.Icons.PerformanceChassisLevel3Item2);
		ACarConfig.Icons.PerformanceChassisLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisLevel3Item3", DefaultCarConfig.Icons.PerformanceChassisLevel3Item3);
		ACarConfig.Icons.PerformanceChassisJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceChassisJunkmanItem", DefaultCarConfig.Icons.PerformanceChassisJunkmanItem);
		ACarConfig.Icons.PerformanceNitrousLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel1Item1", DefaultCarConfig.Icons.PerformanceNitrousLevel1Item1);
		ACarConfig.Icons.PerformanceNitrousLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel1Item2", DefaultCarConfig.Icons.PerformanceNitrousLevel1Item2);
		ACarConfig.Icons.PerformanceNitrousLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel1Item3", DefaultCarConfig.Icons.PerformanceNitrousLevel1Item3);
		ACarConfig.Icons.PerformanceNitrousLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel2Item1", DefaultCarConfig.Icons.PerformanceNitrousLevel2Item1);
		ACarConfig.Icons.PerformanceNitrousLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel2Item2", DefaultCarConfig.Icons.PerformanceNitrousLevel2Item2);
		ACarConfig.Icons.PerformanceNitrousLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel2Item3", DefaultCarConfig.Icons.PerformanceNitrousLevel2Item3);
		ACarConfig.Icons.PerformanceNitrousLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel3Item1", DefaultCarConfig.Icons.PerformanceNitrousLevel3Item1);
		ACarConfig.Icons.PerformanceNitrousLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel3Item2", DefaultCarConfig.Icons.PerformanceNitrousLevel3Item2);
		ACarConfig.Icons.PerformanceNitrousLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousLevel3Item3", DefaultCarConfig.Icons.PerformanceNitrousLevel3Item3);
		ACarConfig.Icons.PerformanceNitrousJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceNitrousJunkmanItem", DefaultCarConfig.Icons.PerformanceNitrousJunkmanItem);
		ACarConfig.Icons.PerformanceTiresLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel1Item1", DefaultCarConfig.Icons.PerformanceTiresLevel1Item1);
		ACarConfig.Icons.PerformanceTiresLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel1Item2", DefaultCarConfig.Icons.PerformanceTiresLevel1Item2);
		ACarConfig.Icons.PerformanceTiresLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel1Item3", DefaultCarConfig.Icons.PerformanceTiresLevel1Item3);
		ACarConfig.Icons.PerformanceTiresLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel2Item1", DefaultCarConfig.Icons.PerformanceTiresLevel2Item1);
		ACarConfig.Icons.PerformanceTiresLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel2Item2", DefaultCarConfig.Icons.PerformanceTiresLevel2Item2);
		ACarConfig.Icons.PerformanceTiresLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel2Item3", DefaultCarConfig.Icons.PerformanceTiresLevel2Item3);
		ACarConfig.Icons.PerformanceTiresLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel3Item1", DefaultCarConfig.Icons.PerformanceTiresLevel3Item1);
		ACarConfig.Icons.PerformanceTiresLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel3Item2", DefaultCarConfig.Icons.PerformanceTiresLevel3Item2);
		ACarConfig.Icons.PerformanceTiresLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresLevel3Item3", DefaultCarConfig.Icons.PerformanceTiresLevel3Item3);
		ACarConfig.Icons.PerformanceTiresJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceTiresJunkmanItem", DefaultCarConfig.Icons.PerformanceTiresJunkmanItem);
		ACarConfig.Icons.PerformanceBrakesLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel1Item1", DefaultCarConfig.Icons.PerformanceBrakesLevel1Item1);
		ACarConfig.Icons.PerformanceBrakesLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel1Item2", DefaultCarConfig.Icons.PerformanceBrakesLevel1Item2);
		ACarConfig.Icons.PerformanceBrakesLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel1Item3", DefaultCarConfig.Icons.PerformanceBrakesLevel1Item3);
		ACarConfig.Icons.PerformanceBrakesLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel2Item1", DefaultCarConfig.Icons.PerformanceBrakesLevel2Item1);
		ACarConfig.Icons.PerformanceBrakesLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel2Item2", DefaultCarConfig.Icons.PerformanceBrakesLevel2Item2);
		ACarConfig.Icons.PerformanceBrakesLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel2Item3", DefaultCarConfig.Icons.PerformanceBrakesLevel2Item3);
		ACarConfig.Icons.PerformanceBrakesLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel3Item1", DefaultCarConfig.Icons.PerformanceBrakesLevel3Item1);
		ACarConfig.Icons.PerformanceBrakesLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel3Item2", DefaultCarConfig.Icons.PerformanceBrakesLevel3Item2);
		ACarConfig.Icons.PerformanceBrakesLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel3Item3", DefaultCarConfig.Icons.PerformanceBrakesLevel3Item3);
		ACarConfig.Icons.PerformanceBrakesLevel4Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel4Item1", DefaultCarConfig.Icons.PerformanceBrakesLevel4Item1);
		ACarConfig.Icons.PerformanceBrakesLevel4Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel4Item2", DefaultCarConfig.Icons.PerformanceBrakesLevel4Item2);
		ACarConfig.Icons.PerformanceBrakesLevel4Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesLevel4Item3", DefaultCarConfig.Icons.PerformanceBrakesLevel4Item3);
		ACarConfig.Icons.PerformanceBrakesJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceBrakesJunkmanItem", DefaultCarConfig.Icons.PerformanceBrakesJunkmanItem);
		ACarConfig.Icons.PerformanceTurboLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel1Item1", DefaultCarConfig.Icons.PerformanceTurboLevel1Item1);
		ACarConfig.Icons.PerformanceTurboLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel1Item2", DefaultCarConfig.Icons.PerformanceTurboLevel1Item2);
		ACarConfig.Icons.PerformanceTurboLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel1Item3", DefaultCarConfig.Icons.PerformanceTurboLevel1Item3);
		ACarConfig.Icons.PerformanceTurboLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel2Item1", DefaultCarConfig.Icons.PerformanceTurboLevel2Item1);
		ACarConfig.Icons.PerformanceTurboLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel2Item2", DefaultCarConfig.Icons.PerformanceTurboLevel2Item2);
		ACarConfig.Icons.PerformanceTurboLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel2Item3", DefaultCarConfig.Icons.PerformanceTurboLevel2Item3);
		ACarConfig.Icons.PerformanceTurboLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel3Item1", DefaultCarConfig.Icons.PerformanceTurboLevel3Item1);
		ACarConfig.Icons.PerformanceTurboLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel3Item2", DefaultCarConfig.Icons.PerformanceTurboLevel3Item2);
		ACarConfig.Icons.PerformanceTurboLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboLevel3Item3", DefaultCarConfig.Icons.PerformanceTurboLevel3Item3);
		ACarConfig.Icons.PerformanceTurboJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceTurboJunkmanItem", DefaultCarConfig.Icons.PerformanceTurboJunkmanItem);
		ACarConfig.Icons.PerformanceSuperchargerLevel1Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel1Item1", DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item1);
		ACarConfig.Icons.PerformanceSuperchargerLevel1Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel1Item2", DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item2);
		ACarConfig.Icons.PerformanceSuperchargerLevel1Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel1Item3", DefaultCarConfig.Icons.PerformanceSuperchargerLevel1Item3);
		ACarConfig.Icons.PerformanceSuperchargerLevel2Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel2Item1", DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item1);
		ACarConfig.Icons.PerformanceSuperchargerLevel2Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel2Item2", DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item2);
		ACarConfig.Icons.PerformanceSuperchargerLevel2Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel2Item3", DefaultCarConfig.Icons.PerformanceSuperchargerLevel2Item3);
		ACarConfig.Icons.PerformanceSuperchargerLevel3Item1 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel3Item1", DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item1);
		ACarConfig.Icons.PerformanceSuperchargerLevel3Item2 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel3Item2", DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item2);
		ACarConfig.Icons.PerformanceSuperchargerLevel3Item3 = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerLevel3Item3", DefaultCarConfig.Icons.PerformanceSuperchargerLevel3Item3);
		ACarConfig.Icons.PerformanceSuperchargerJunkmanItem = mINI_ReadHash(CarINI, "Icons", "PerformanceSuperchargerJunkmanItem", DefaultCarConfig.Icons.PerformanceSuperchargerJunkmanItem);

		// Names
		ACarConfig.Names.Parts = mINI_ReadHash(CarINI, "Names", "Parts", DefaultCarConfig.Names.Parts);
		ACarConfig.Names.PartsBodyKits = mINI_ReadHash(CarINI, "Names", "PartsBodykits", DefaultCarConfig.Names.PartsBodyKits);
		ACarConfig.Names.PartsSpoilers = mINI_ReadHash(CarINI, "Names", "PartsSpoilers", DefaultCarConfig.Names.PartsSpoilers);
		ACarConfig.Names.PartsRims = mINI_ReadHash(CarINI, "Names", "PartsRims", DefaultCarConfig.Names.PartsRims);
		ACarConfig.Names.PartsRimsBrand = mINI_ReadHash(CarINI, "Names", "PartsRimsBrand", DefaultCarConfig.Names.PartsRimsBrand);
		ACarConfig.Names.PartsRimsCustom = mINI_ReadHash(CarINI, "Names", "PartsRimsCustom", DefaultCarConfig.Names.PartsRimsCustom);
		ACarConfig.Names.PartsHoods = mINI_ReadHash(CarINI, "Names", "PartsHoods", DefaultCarConfig.Names.PartsHoods);
		ACarConfig.Names.PartsRoofScoops = mINI_ReadHash(CarINI, "Names", "PartsRoofScoops", DefaultCarConfig.Names.PartsRoofScoops);
		ACarConfig.Names.PartsInterior = mINI_ReadHash(CarINI, "Names", "PartsInterior", DefaultCarConfig.Names.PartsInterior);
		ACarConfig.Names.PartsRoof = mINI_ReadHash(CarINI, "Names", "PartsRoof", DefaultCarConfig.Names.PartsRoof);
		ACarConfig.Names.PartsBrakes = mINI_ReadHash(CarINI, "Names", "PartsBrakes", DefaultCarConfig.Names.PartsBrakes);
		ACarConfig.Names.PartsHeadlights = mINI_ReadHash(CarINI, "Names", "PartsHeadlights", DefaultCarConfig.Names.PartsHeadlights);
		ACarConfig.Names.PartsTaillights = mINI_ReadHash(CarINI, "Names", "PartsTaillights", DefaultCarConfig.Names.PartsTaillights);
		ACarConfig.Names.PartsMirrors = mINI_ReadHash(CarINI, "Names", "PartsMirrors", DefaultCarConfig.Names.PartsMirrors);
		ACarConfig.Names.PartsAttachments = mINI_ReadHash(CarINI, "Names", "PartsAttachments", DefaultCarConfig.Names.PartsAttachments);
		ACarConfig.Names.PartsAttachment0 = mINI_ReadHash(CarINI, "Names", "PartsAttachment0", DefaultCarConfig.Names.PartsAttachment0);
		ACarConfig.Names.PartsAttachment1 = mINI_ReadHash(CarINI, "Names", "PartsAttachment1", DefaultCarConfig.Names.PartsAttachment1);
		ACarConfig.Names.PartsAttachment2 = mINI_ReadHash(CarINI, "Names", "PartsAttachment2", DefaultCarConfig.Names.PartsAttachment2);
		ACarConfig.Names.PartsAttachment3 = mINI_ReadHash(CarINI, "Names", "PartsAttachment3", DefaultCarConfig.Names.PartsAttachment3);
		ACarConfig.Names.PartsAttachment4 = mINI_ReadHash(CarINI, "Names", "PartsAttachment4", DefaultCarConfig.Names.PartsAttachment4);
		ACarConfig.Names.PartsAttachment5 = mINI_ReadHash(CarINI, "Names", "PartsAttachment5", DefaultCarConfig.Names.PartsAttachment5);
		ACarConfig.Names.PartsAttachment6 = mINI_ReadHash(CarINI, "Names", "PartsAttachment6", DefaultCarConfig.Names.PartsAttachment6);
		ACarConfig.Names.PartsAttachment7 = mINI_ReadHash(CarINI, "Names", "PartsAttachment7", DefaultCarConfig.Names.PartsAttachment7);
		ACarConfig.Names.PartsAttachment8 = mINI_ReadHash(CarINI, "Names", "PartsAttachment8", DefaultCarConfig.Names.PartsAttachment8);
		ACarConfig.Names.PartsAttachment9 = mINI_ReadHash(CarINI, "Names", "PartsAttachment9", DefaultCarConfig.Names.PartsAttachment9);
		ACarConfig.Names.Performance = mINI_ReadHash(CarINI, "Names", "Performance", DefaultCarConfig.Names.Performance);
		ACarConfig.Names.PerformanceEngine = mINI_ReadHash(CarINI, "Names", "PerformanceEngine", DefaultCarConfig.Names.PerformanceEngine);
		ACarConfig.Names.PerformanceTransmission = mINI_ReadHash(CarINI, "Names", "PerformanceTransmission", DefaultCarConfig.Names.PerformanceTransmission);
		ACarConfig.Names.PerformanceChassis = mINI_ReadHash(CarINI, "Names", "PerformanceChassis", DefaultCarConfig.Names.PerformanceChassis);
		ACarConfig.Names.PerformanceNitrous = mINI_ReadHash(CarINI, "Names", "PerformanceNitrous", DefaultCarConfig.Names.PerformanceNitrous);
		ACarConfig.Names.PerformanceTires = mINI_ReadHash(CarINI, "Names", "PerformanceTires", DefaultCarConfig.Names.PerformanceTires);
		ACarConfig.Names.PerformanceBrakes = mINI_ReadHash(CarINI, "Names", "PerformanceBrakes", DefaultCarConfig.Names.PerformanceBrakes);
		ACarConfig.Names.PerformanceTurbo = mINI_ReadHash(CarINI, "Names", "PerformanceTurbo", DefaultCarConfig.Names.PerformanceTurbo);
		ACarConfig.Names.PerformanceSupercharger = mINI_ReadHash(CarINI, "Names", "PerformanceSupercharger", DefaultCarConfig.Names.PerformanceSupercharger);
		ACarConfig.Names.Visual = mINI_ReadHash(CarINI, "Names", "Visual", DefaultCarConfig.Names.Visual);
		ACarConfig.Names.VisualPaint = mINI_ReadHash(CarINI, "Names", "VisualPaint", DefaultCarConfig.Names.VisualPaint);
		ACarConfig.Names.VisualPaintCustom = mINI_ReadHash(CarINI, "Names", "VisualPaintCustom", DefaultCarConfig.Names.VisualPaintCustom);
		ACarConfig.Names.VisualVinyls = mINI_ReadHash(CarINI, "Names", "VisualVinyls", DefaultCarConfig.Names.VisualVinyls);
		ACarConfig.Names.VisualVinylsCustom = mINI_ReadHash(CarINI, "Names", "VisualVinylsCustom", DefaultCarConfig.Names.VisualVinylsCustom);
		ACarConfig.Names.VisualVinylsGroup = mINI_ReadHash(CarINI, "Names", "VisualVinylsGroup", DefaultCarConfig.Names.VisualVinylsGroup);
		ACarConfig.Names.VisualVinylsColor = mINI_ReadHash(CarINI, "Names", "VisualVinylsColor", DefaultCarConfig.Names.VisualVinylsColor);
		ACarConfig.Names.VisualRimPaint = mINI_ReadHash(CarINI, "Names", "VisualRimPaint", DefaultCarConfig.Names.VisualRimPaint);
		ACarConfig.Names.VisualWindowTint = mINI_ReadHash(CarINI, "Names", "VisualWindowTint", DefaultCarConfig.Names.VisualWindowTint);
		ACarConfig.Names.VisualDecals = mINI_ReadHash(CarINI, "Names", "VisualDecals", DefaultCarConfig.Names.VisualDecals);
		ACarConfig.Names.VisualDecalsPosition = mINI_ReadHash(CarINI, "Names", "VisualDecalsPosition", DefaultCarConfig.Names.VisualDecalsPosition);
		ACarConfig.Names.VisualDecalsLocation = mINI_ReadHash(CarINI, "Names", "VisualDecalsLocation", DefaultCarConfig.Names.VisualDecalsLocation);
		ACarConfig.Names.VisualDecalsWindshield = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield", DefaultCarConfig.Names.VisualDecalsWindshield);
		ACarConfig.Names.VisualDecalsWindshield1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield1", DefaultCarConfig.Names.VisualDecalsWindshield1);
		ACarConfig.Names.VisualDecalsWindshield2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield2", DefaultCarConfig.Names.VisualDecalsWindshield2);
		ACarConfig.Names.VisualDecalsWindshield3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield3", DefaultCarConfig.Names.VisualDecalsWindshield3);
		ACarConfig.Names.VisualDecalsWindshield4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield4", DefaultCarConfig.Names.VisualDecalsWindshield4);
		ACarConfig.Names.VisualDecalsWindshield5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield5", DefaultCarConfig.Names.VisualDecalsWindshield5);
		ACarConfig.Names.VisualDecalsWindshield6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield6", DefaultCarConfig.Names.VisualDecalsWindshield6);
		ACarConfig.Names.VisualDecalsWindshield7 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield7", DefaultCarConfig.Names.VisualDecalsWindshield7);
		ACarConfig.Names.VisualDecalsWindshield8 = mINI_ReadHash(CarINI, "Names", "VisualDecalsWindshield8", DefaultCarConfig.Names.VisualDecalsWindshield8);
		ACarConfig.Names.VisualDecalsRearWindow = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow", DefaultCarConfig.Names.VisualDecalsRearWindow);
		ACarConfig.Names.VisualDecalsRearWindow1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow1", DefaultCarConfig.Names.VisualDecalsRearWindow1);
		ACarConfig.Names.VisualDecalsRearWindow2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow2", DefaultCarConfig.Names.VisualDecalsRearWindow2);
		ACarConfig.Names.VisualDecalsRearWindow3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow3", DefaultCarConfig.Names.VisualDecalsRearWindow3);
		ACarConfig.Names.VisualDecalsRearWindow4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow4", DefaultCarConfig.Names.VisualDecalsRearWindow4);
		ACarConfig.Names.VisualDecalsRearWindow5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow5", DefaultCarConfig.Names.VisualDecalsRearWindow5);
		ACarConfig.Names.VisualDecalsRearWindow6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow6", DefaultCarConfig.Names.VisualDecalsRearWindow6);
		ACarConfig.Names.VisualDecalsRearWindow7 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow7", DefaultCarConfig.Names.VisualDecalsRearWindow7);
		ACarConfig.Names.VisualDecalsRearWindow8 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRearWindow8", DefaultCarConfig.Names.VisualDecalsRearWindow8);
		ACarConfig.Names.VisualDecalsLeftDoor = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor", DefaultCarConfig.Names.VisualDecalsLeftDoor);
		ACarConfig.Names.VisualDecalsLeftDoor1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor1", DefaultCarConfig.Names.VisualDecalsLeftDoor1);
		ACarConfig.Names.VisualDecalsLeftDoor2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor2", DefaultCarConfig.Names.VisualDecalsLeftDoor2);
		ACarConfig.Names.VisualDecalsLeftDoor3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor3", DefaultCarConfig.Names.VisualDecalsLeftDoor3);
		ACarConfig.Names.VisualDecalsLeftDoor4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor4", DefaultCarConfig.Names.VisualDecalsLeftDoor4);
		ACarConfig.Names.VisualDecalsLeftDoor5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor5", DefaultCarConfig.Names.VisualDecalsLeftDoor5);
		ACarConfig.Names.VisualDecalsLeftDoor6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftDoor6", DefaultCarConfig.Names.VisualDecalsLeftDoor6);
		ACarConfig.Names.VisualDecalsRightDoor = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor", DefaultCarConfig.Names.VisualDecalsRightDoor);
		ACarConfig.Names.VisualDecalsRightDoor1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor1", DefaultCarConfig.Names.VisualDecalsRightDoor1);
		ACarConfig.Names.VisualDecalsRightDoor2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor2", DefaultCarConfig.Names.VisualDecalsRightDoor2);
		ACarConfig.Names.VisualDecalsRightDoor3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor3", DefaultCarConfig.Names.VisualDecalsRightDoor3);
		ACarConfig.Names.VisualDecalsRightDoor4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor4", DefaultCarConfig.Names.VisualDecalsRightDoor4);
		ACarConfig.Names.VisualDecalsRightDoor5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor5", DefaultCarConfig.Names.VisualDecalsRightDoor5);
		ACarConfig.Names.VisualDecalsRightDoor6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightDoor6", DefaultCarConfig.Names.VisualDecalsRightDoor6);
		ACarConfig.Names.VisualDecalsLeftQuarter = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter", DefaultCarConfig.Names.VisualDecalsLeftQuarter);
		ACarConfig.Names.VisualDecalsLeftQuarter1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter1", DefaultCarConfig.Names.VisualDecalsLeftQuarter1);
		ACarConfig.Names.VisualDecalsLeftQuarter2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter2", DefaultCarConfig.Names.VisualDecalsLeftQuarter2);
		ACarConfig.Names.VisualDecalsLeftQuarter3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter3", DefaultCarConfig.Names.VisualDecalsLeftQuarter3);
		ACarConfig.Names.VisualDecalsLeftQuarter4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter4", DefaultCarConfig.Names.VisualDecalsLeftQuarter4);
		ACarConfig.Names.VisualDecalsLeftQuarter5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter5", DefaultCarConfig.Names.VisualDecalsLeftQuarter5);
		ACarConfig.Names.VisualDecalsLeftQuarter6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter6", DefaultCarConfig.Names.VisualDecalsLeftQuarter6);
		ACarConfig.Names.VisualDecalsLeftQuarter7 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter7", DefaultCarConfig.Names.VisualDecalsLeftQuarter7);
		ACarConfig.Names.VisualDecalsLeftQuarter8 = mINI_ReadHash(CarINI, "Names", "VisualDecalsLeftQuarter8", DefaultCarConfig.Names.VisualDecalsLeftQuarter8);
		ACarConfig.Names.VisualDecalsRightQuarter = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter", DefaultCarConfig.Names.VisualDecalsRightQuarter);
		ACarConfig.Names.VisualDecalsRightQuarter1 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter1", DefaultCarConfig.Names.VisualDecalsRightQuarter1);
		ACarConfig.Names.VisualDecalsRightQuarter2 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter2", DefaultCarConfig.Names.VisualDecalsRightQuarter2);
		ACarConfig.Names.VisualDecalsRightQuarter3 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter3", DefaultCarConfig.Names.VisualDecalsRightQuarter3);
		ACarConfig.Names.VisualDecalsRightQuarter4 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter4", DefaultCarConfig.Names.VisualDecalsRightQuarter4);
		ACarConfig.Names.VisualDecalsRightQuarter5 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter5", DefaultCarConfig.Names.VisualDecalsRightQuarter5);
		ACarConfig.Names.VisualDecalsRightQuarter6 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter6", DefaultCarConfig.Names.VisualDecalsRightQuarter6);
		ACarConfig.Names.VisualDecalsRightQuarter7 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter7", DefaultCarConfig.Names.VisualDecalsRightQuarter7);
		ACarConfig.Names.VisualDecalsRightQuarter8 = mINI_ReadHash(CarINI, "Names", "VisualDecalsRightQuarter8", DefaultCarConfig.Names.VisualDecalsRightQuarter8);
		ACarConfig.Names.VisualNumbers = mINI_ReadHash(CarINI, "Names", "VisualNumbers", DefaultCarConfig.Names.VisualNumbers);
		ACarConfig.Names.VisualCustomGauges = mINI_ReadHash(CarINI, "Names", "VisualCustomGauges", DefaultCarConfig.Names.VisualCustomGauges);
		ACarConfig.Names.VisualDriver = mINI_ReadHash(CarINI, "Names", "VisualDriver", DefaultCarConfig.Names.VisualDriver);
		ACarConfig.Names.VisualLicensePlate = mINI_ReadHash(CarINI, "Names", "VisualLicensePlate", DefaultCarConfig.Names.VisualLicensePlate);
		ACarConfig.Names.VisualTires = mINI_ReadHash(CarINI, "Names", "VisualTires", DefaultCarConfig.Names.VisualTires);
		ACarConfig.Names.VisualNeon = mINI_ReadHash(CarINI, "Names", "VisualNeon", DefaultCarConfig.Names.VisualNeon);
		ACarConfig.Names.BackroomParts = mINI_ReadHash(CarINI, "Names", "BackroomParts", DefaultCarConfig.Names.BackroomParts);
		ACarConfig.Names.BackroomPerformance = mINI_ReadHash(CarINI, "Names", "BackroomPerformance", DefaultCarConfig.Names.BackroomPerformance);
		ACarConfig.Names.BackroomVisual = mINI_ReadHash(CarINI, "Names", "BackroomVisual", DefaultCarConfig.Names.BackroomVisual);
		ACarConfig.Names.PerformanceEngineStock = mINI_ReadHash(CarINI, "Names", "PerformanceEngineStock", DefaultCarConfig.Names.PerformanceEngineStock);
		ACarConfig.Names.PerformanceEngineStreet = mINI_ReadHash(CarINI, "Names", "PerformanceEngineStreet", DefaultCarConfig.Names.PerformanceEngineStreet);
		ACarConfig.Names.PerformanceEngineSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceEngineSuperStreet", DefaultCarConfig.Names.PerformanceEngineSuperStreet);
		ACarConfig.Names.PerformanceEngineRace = mINI_ReadHash(CarINI, "Names", "PerformanceEngineRace", DefaultCarConfig.Names.PerformanceEngineRace);
		ACarConfig.Names.PerformanceEnginePro = mINI_ReadHash(CarINI, "Names", "PerformanceEnginePro", DefaultCarConfig.Names.PerformanceEnginePro);
		ACarConfig.Names.PerformanceEngineSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceEngineSuperPro", DefaultCarConfig.Names.PerformanceEngineSuperPro);
		ACarConfig.Names.PerformanceEngineUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceEngineUltimate", DefaultCarConfig.Names.PerformanceEngineUltimate);
		ACarConfig.Names.PerformanceEngineJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceEngineJunkman", DefaultCarConfig.Names.PerformanceEngineJunkman);
		ACarConfig.Names.PerformanceTransmissionStock = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionStock", DefaultCarConfig.Names.PerformanceTransmissionStock);
		ACarConfig.Names.PerformanceTransmissionStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionStreet", DefaultCarConfig.Names.PerformanceTransmissionStreet);
		ACarConfig.Names.PerformanceTransmissionSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionSuperStreet", DefaultCarConfig.Names.PerformanceTransmissionSuperStreet);
		ACarConfig.Names.PerformanceTransmissionRace = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionRace", DefaultCarConfig.Names.PerformanceTransmissionRace);
		ACarConfig.Names.PerformanceTransmissionPro = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionPro", DefaultCarConfig.Names.PerformanceTransmissionPro);
		ACarConfig.Names.PerformanceTransmissionSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionSuperPro", DefaultCarConfig.Names.PerformanceTransmissionSuperPro);
		ACarConfig.Names.PerformanceTransmissionUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionUltimate", DefaultCarConfig.Names.PerformanceTransmissionUltimate);
		ACarConfig.Names.PerformanceTransmissionJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionJunkman", DefaultCarConfig.Names.PerformanceTransmissionJunkman);
		ACarConfig.Names.PerformanceChassisStock = mINI_ReadHash(CarINI, "Names", "PerformanceChassisStock", DefaultCarConfig.Names.PerformanceChassisStock);
		ACarConfig.Names.PerformanceChassisStreet = mINI_ReadHash(CarINI, "Names", "PerformanceChassisStreet", DefaultCarConfig.Names.PerformanceChassisStreet);
		ACarConfig.Names.PerformanceChassisSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceChassisSuperStreet", DefaultCarConfig.Names.PerformanceChassisSuperStreet);
		ACarConfig.Names.PerformanceChassisRace = mINI_ReadHash(CarINI, "Names", "PerformanceChassisRace", DefaultCarConfig.Names.PerformanceChassisRace);
		ACarConfig.Names.PerformanceChassisPro = mINI_ReadHash(CarINI, "Names", "PerformanceChassisPro", DefaultCarConfig.Names.PerformanceChassisPro);
		ACarConfig.Names.PerformanceChassisSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceChassisSuperPro", DefaultCarConfig.Names.PerformanceChassisSuperPro);
		ACarConfig.Names.PerformanceChassisUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceChassisUltimate", DefaultCarConfig.Names.PerformanceChassisUltimate);
		ACarConfig.Names.PerformanceChassisJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceChassisJunkman", DefaultCarConfig.Names.PerformanceChassisJunkman);
		ACarConfig.Names.PerformanceNitrousStock = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousStock", DefaultCarConfig.Names.PerformanceNitrousStock);
		ACarConfig.Names.PerformanceNitrousStreet = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousStreet", DefaultCarConfig.Names.PerformanceNitrousStreet);
		ACarConfig.Names.PerformanceNitrousSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousSuperStreet", DefaultCarConfig.Names.PerformanceNitrousSuperStreet);
		ACarConfig.Names.PerformanceNitrousRace = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousRace", DefaultCarConfig.Names.PerformanceNitrousRace);
		ACarConfig.Names.PerformanceNitrousPro = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousPro", DefaultCarConfig.Names.PerformanceNitrousPro);
		ACarConfig.Names.PerformanceNitrousSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousSuperPro", DefaultCarConfig.Names.PerformanceNitrousSuperPro);
		ACarConfig.Names.PerformanceNitrousUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousUltimate", DefaultCarConfig.Names.PerformanceNitrousUltimate);
		ACarConfig.Names.PerformanceNitrousJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousJunkman", DefaultCarConfig.Names.PerformanceNitrousJunkman);
		ACarConfig.Names.PerformanceTiresStock = mINI_ReadHash(CarINI, "Names", "PerformanceTiresStock", DefaultCarConfig.Names.PerformanceTiresStock);
		ACarConfig.Names.PerformanceTiresStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTiresStreet", DefaultCarConfig.Names.PerformanceTiresStreet);
		ACarConfig.Names.PerformanceTiresSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTiresSuperStreet", DefaultCarConfig.Names.PerformanceTiresSuperStreet);
		ACarConfig.Names.PerformanceTiresRace = mINI_ReadHash(CarINI, "Names", "PerformanceTiresRace", DefaultCarConfig.Names.PerformanceTiresRace);
		ACarConfig.Names.PerformanceTiresPro = mINI_ReadHash(CarINI, "Names", "PerformanceTiresPro", DefaultCarConfig.Names.PerformanceTiresPro);
		ACarConfig.Names.PerformanceTiresSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceTiresSuperPro", DefaultCarConfig.Names.PerformanceTiresSuperPro);
		ACarConfig.Names.PerformanceTiresUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceTiresUltimate", DefaultCarConfig.Names.PerformanceTiresUltimate);
		ACarConfig.Names.PerformanceTiresJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceTiresJunkman", DefaultCarConfig.Names.PerformanceTiresJunkman);
		ACarConfig.Names.PerformanceBrakesStock = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesStock", DefaultCarConfig.Names.PerformanceBrakesStock);
		ACarConfig.Names.PerformanceBrakesStreet = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesStreet", DefaultCarConfig.Names.PerformanceBrakesStreet);
		ACarConfig.Names.PerformanceBrakesSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesSuperStreet", DefaultCarConfig.Names.PerformanceBrakesSuperStreet);
		ACarConfig.Names.PerformanceBrakesRace = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesRace", DefaultCarConfig.Names.PerformanceBrakesRace);
		ACarConfig.Names.PerformanceBrakesPro = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesPro", DefaultCarConfig.Names.PerformanceBrakesPro);
		ACarConfig.Names.PerformanceBrakesSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesSuperPro", DefaultCarConfig.Names.PerformanceBrakesSuperPro);
		ACarConfig.Names.PerformanceBrakesUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesUltimate", DefaultCarConfig.Names.PerformanceBrakesUltimate);
		ACarConfig.Names.PerformanceBrakesJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesJunkman", DefaultCarConfig.Names.PerformanceBrakesJunkman);
		ACarConfig.Names.PerformanceTurboStock = mINI_ReadHash(CarINI, "Names", "PerformanceTurboStock", DefaultCarConfig.Names.PerformanceTurboStock);
		ACarConfig.Names.PerformanceTurboStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTurboStreet", DefaultCarConfig.Names.PerformanceTurboStreet);
		ACarConfig.Names.PerformanceTurboSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceTurboSuperStreet", DefaultCarConfig.Names.PerformanceTurboSuperStreet);
		ACarConfig.Names.PerformanceTurboRace = mINI_ReadHash(CarINI, "Names", "PerformanceTurboRace", DefaultCarConfig.Names.PerformanceTurboRace);
		ACarConfig.Names.PerformanceTurboPro = mINI_ReadHash(CarINI, "Names", "PerformanceTurboPro", DefaultCarConfig.Names.PerformanceTurboPro);
		ACarConfig.Names.PerformanceTurboSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceTurboSuperPro", DefaultCarConfig.Names.PerformanceTurboSuperPro);
		ACarConfig.Names.PerformanceTurboUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceTurboUltimate", DefaultCarConfig.Names.PerformanceTurboUltimate);
		ACarConfig.Names.PerformanceTurboJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceTurboJunkman", DefaultCarConfig.Names.PerformanceTurboJunkman);
		ACarConfig.Names.PerformanceSuperchargerStock = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerStock", DefaultCarConfig.Names.PerformanceSuperchargerStock);
		ACarConfig.Names.PerformanceSuperchargerStreet = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerStreet", DefaultCarConfig.Names.PerformanceSuperchargerStreet);
		ACarConfig.Names.PerformanceSuperchargerSuperStreet = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerSuperStreet", DefaultCarConfig.Names.PerformanceSuperchargerSuperStreet);
		ACarConfig.Names.PerformanceSuperchargerRace = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerRace", DefaultCarConfig.Names.PerformanceSuperchargerRace);
		ACarConfig.Names.PerformanceSuperchargerPro = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerPro", DefaultCarConfig.Names.PerformanceSuperchargerPro);
		ACarConfig.Names.PerformanceSuperchargerSuperPro = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerSuperPro", DefaultCarConfig.Names.PerformanceSuperchargerSuperPro);
		ACarConfig.Names.PerformanceSuperchargerUltimate = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerUltimate", DefaultCarConfig.Names.PerformanceSuperchargerUltimate);
		ACarConfig.Names.PerformanceSuperchargerJunkman = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerJunkman", DefaultCarConfig.Names.PerformanceSuperchargerJunkman);
		ACarConfig.Names.PerformanceEngineLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel1Item1", DefaultCarConfig.Names.PerformanceEngineLevel1Item1);
		ACarConfig.Names.PerformanceEngineLevel1Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel1Item2", DefaultCarConfig.Names.PerformanceEngineLevel1Item2);
		ACarConfig.Names.PerformanceEngineLevel1Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel1Item3", DefaultCarConfig.Names.PerformanceEngineLevel1Item3);
		ACarConfig.Names.PerformanceEngineLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel2Item1", DefaultCarConfig.Names.PerformanceEngineLevel2Item1);
		ACarConfig.Names.PerformanceEngineLevel2Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel2Item2", DefaultCarConfig.Names.PerformanceEngineLevel2Item2);
		ACarConfig.Names.PerformanceEngineLevel2Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel2Item3", DefaultCarConfig.Names.PerformanceEngineLevel2Item3);
		ACarConfig.Names.PerformanceEngineLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel3Item1", DefaultCarConfig.Names.PerformanceEngineLevel3Item1);
		ACarConfig.Names.PerformanceEngineLevel3Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel3Item2", DefaultCarConfig.Names.PerformanceEngineLevel3Item2);
		ACarConfig.Names.PerformanceEngineLevel3Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel3Item3", DefaultCarConfig.Names.PerformanceEngineLevel3Item3);
		ACarConfig.Names.PerformanceEngineLevel4Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel4Item1", DefaultCarConfig.Names.PerformanceEngineLevel4Item1);
		ACarConfig.Names.PerformanceEngineLevel4Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel4Item2", DefaultCarConfig.Names.PerformanceEngineLevel4Item2);
		ACarConfig.Names.PerformanceEngineLevel4Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel4Item3", DefaultCarConfig.Names.PerformanceEngineLevel4Item3);
		ACarConfig.Names.PerformanceEngineLevel2Item1Rotary = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel2Item1Rotary", DefaultCarConfig.Names.PerformanceEngineLevel2Item1Rotary);
		ACarConfig.Names.PerformanceEngineLevel4Item1Rotary = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel4Item1Rotary", DefaultCarConfig.Names.PerformanceEngineLevel4Item1Rotary);
		ACarConfig.Names.PerformanceEngineLevel4Item3Castrol = mINI_ReadHash(CarINI, "Names", "PerformanceEngineLevel4Item3Castrol", DefaultCarConfig.Names.PerformanceEngineLevel4Item3Castrol);
		ACarConfig.Names.PerformanceEngineJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceEngineJunkmanItem", DefaultCarConfig.Names.PerformanceEngineJunkmanItem);
		ACarConfig.Names.PerformanceTransmissionLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel1Item1", DefaultCarConfig.Names.PerformanceTransmissionLevel1Item1);
		ACarConfig.Names.PerformanceTransmissionLevel1Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel1Item2", DefaultCarConfig.Names.PerformanceTransmissionLevel1Item2);
		ACarConfig.Names.PerformanceTransmissionLevel1Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel1Item3", DefaultCarConfig.Names.PerformanceTransmissionLevel1Item3);
		ACarConfig.Names.PerformanceTransmissionLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel2Item1", DefaultCarConfig.Names.PerformanceTransmissionLevel2Item1);
		ACarConfig.Names.PerformanceTransmissionLevel2Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel2Item2", DefaultCarConfig.Names.PerformanceTransmissionLevel2Item2);
		ACarConfig.Names.PerformanceTransmissionLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel3Item1", DefaultCarConfig.Names.PerformanceTransmissionLevel3Item1);
		ACarConfig.Names.PerformanceTransmissionLevel3Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel3Item2", DefaultCarConfig.Names.PerformanceTransmissionLevel3Item2);
		ACarConfig.Names.PerformanceTransmissionLevel4Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel4Item1", DefaultCarConfig.Names.PerformanceTransmissionLevel4Item1);
		ACarConfig.Names.PerformanceTransmissionLevel4Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionLevel4Item2", DefaultCarConfig.Names.PerformanceTransmissionLevel4Item2);
		ACarConfig.Names.PerformanceTransmissionJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceTransmissionJunkmanItem", DefaultCarConfig.Names.PerformanceTransmissionJunkmanItem);
		ACarConfig.Names.PerformanceChassisLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel1Item1", DefaultCarConfig.Names.PerformanceChassisLevel1Item1);
		ACarConfig.Names.PerformanceChassisLevel1Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel1Item2", DefaultCarConfig.Names.PerformanceChassisLevel1Item2);
		ACarConfig.Names.PerformanceChassisLevel1Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel1Item3", DefaultCarConfig.Names.PerformanceChassisLevel1Item3);
		ACarConfig.Names.PerformanceChassisLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel2Item1", DefaultCarConfig.Names.PerformanceChassisLevel2Item1);
		ACarConfig.Names.PerformanceChassisLevel2Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel2Item2", DefaultCarConfig.Names.PerformanceChassisLevel2Item2);
		ACarConfig.Names.PerformanceChassisLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel3Item1", DefaultCarConfig.Names.PerformanceChassisLevel3Item1);
		ACarConfig.Names.PerformanceChassisLevel3Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel3Item2", DefaultCarConfig.Names.PerformanceChassisLevel3Item2);
		ACarConfig.Names.PerformanceChassisLevel3Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceChassisLevel3Item3", DefaultCarConfig.Names.PerformanceChassisLevel3Item3);
		ACarConfig.Names.PerformanceChassisJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceChassisJunkmanItem", DefaultCarConfig.Names.PerformanceChassisJunkmanItem);
		ACarConfig.Names.PerformanceNitrousLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousLevel1Item1", DefaultCarConfig.Names.PerformanceNitrousLevel1Item1);
		ACarConfig.Names.PerformanceNitrousLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousLevel2Item1", DefaultCarConfig.Names.PerformanceNitrousLevel2Item1);
		ACarConfig.Names.PerformanceNitrousLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousLevel3Item1", DefaultCarConfig.Names.PerformanceNitrousLevel3Item1);
		ACarConfig.Names.PerformanceNitrousJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceNitrousJunkmanItem", DefaultCarConfig.Names.PerformanceNitrousJunkmanItem);
		ACarConfig.Names.PerformanceTiresLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTiresLevel1Item1", DefaultCarConfig.Names.PerformanceTiresLevel1Item1);
		ACarConfig.Names.PerformanceTiresLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTiresLevel2Item1", DefaultCarConfig.Names.PerformanceTiresLevel2Item1);
		ACarConfig.Names.PerformanceTiresLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTiresLevel3Item1", DefaultCarConfig.Names.PerformanceTiresLevel3Item1);
		ACarConfig.Names.PerformanceTiresJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceTiresJunkmanItem", DefaultCarConfig.Names.PerformanceTiresJunkmanItem);
		ACarConfig.Names.PerformanceBrakesLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel1Item1", DefaultCarConfig.Names.PerformanceBrakesLevel1Item1);
		ACarConfig.Names.PerformanceBrakesLevel1Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel1Item2", DefaultCarConfig.Names.PerformanceBrakesLevel1Item2);
		ACarConfig.Names.PerformanceBrakesLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel2Item1", DefaultCarConfig.Names.PerformanceBrakesLevel2Item1);
		ACarConfig.Names.PerformanceBrakesLevel2Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel2Item2", DefaultCarConfig.Names.PerformanceBrakesLevel2Item2);
		ACarConfig.Names.PerformanceBrakesLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel3Item1", DefaultCarConfig.Names.PerformanceBrakesLevel3Item1);
		ACarConfig.Names.PerformanceBrakesLevel3Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel3Item2", DefaultCarConfig.Names.PerformanceBrakesLevel3Item2);
		ACarConfig.Names.PerformanceBrakesLevel4Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel4Item1", DefaultCarConfig.Names.PerformanceBrakesLevel4Item1);
		ACarConfig.Names.PerformanceBrakesLevel4Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel4Item2", DefaultCarConfig.Names.PerformanceBrakesLevel4Item2);
		ACarConfig.Names.PerformanceBrakesLevel4Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesLevel4Item3", DefaultCarConfig.Names.PerformanceBrakesLevel4Item3);
		ACarConfig.Names.PerformanceBrakesJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceBrakesJunkmanItem", DefaultCarConfig.Names.PerformanceBrakesJunkmanItem);
		ACarConfig.Names.PerformanceTurboLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel1Item1", DefaultCarConfig.Names.PerformanceTurboLevel1Item1);
		ACarConfig.Names.PerformanceTurboLevel1Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel1Item2", DefaultCarConfig.Names.PerformanceTurboLevel1Item2);
		ACarConfig.Names.PerformanceTurboLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel2Item1", DefaultCarConfig.Names.PerformanceTurboLevel2Item1);
		ACarConfig.Names.PerformanceTurboLevel2Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel2Item2", DefaultCarConfig.Names.PerformanceTurboLevel2Item2);
		ACarConfig.Names.PerformanceTurboLevel2Item3 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel2Item3", DefaultCarConfig.Names.PerformanceTurboLevel2Item3);
		ACarConfig.Names.PerformanceTurboLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel3Item1", DefaultCarConfig.Names.PerformanceTurboLevel3Item1);
		ACarConfig.Names.PerformanceTurboLevel3Item2 = mINI_ReadHash(CarINI, "Names", "PerformanceTurboLevel3Item2", DefaultCarConfig.Names.PerformanceTurboLevel3Item2);
		ACarConfig.Names.PerformanceTurboJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceTurboJunkmanItem", DefaultCarConfig.Names.PerformanceTurboJunkmanItem);
		ACarConfig.Names.PerformanceSuperchargerLevel1Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerLevel1Item1", DefaultCarConfig.Names.PerformanceSuperchargerLevel1Item1);
		ACarConfig.Names.PerformanceSuperchargerLevel2Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerLevel2Item1", DefaultCarConfig.Names.PerformanceSuperchargerLevel2Item1);
		ACarConfig.Names.PerformanceSuperchargerLevel3Item1 = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerLevel3Item1", DefaultCarConfig.Names.PerformanceSuperchargerLevel3Item1);
		ACarConfig.Names.PerformanceSuperchargerJunkmanItem = mINI_ReadHash(CarINI, "Names", "PerformanceSuperchargerJunkmanItem", DefaultCarConfig.Names.PerformanceSuperchargerJunkmanItem);

		// Cameras
		ACarConfig.Cameras.PartsBodyKits = mINI_ReadVLTHash(CarINI, "Cameras", "PartsBodyKits", DefaultCarConfig.Cameras.PartsBodyKits);
		ACarConfig.Cameras.PartsSpoilers = mINI_ReadVLTHash(CarINI, "Cameras", "PartsSpoilers", DefaultCarConfig.Cameras.PartsSpoilers);
		ACarConfig.Cameras.PartsRims = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRims", DefaultCarConfig.Cameras.PartsRims);
		ACarConfig.Cameras.PartsRimsBrand = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRimsBrand", DefaultCarConfig.Cameras.PartsRimsBrand);
		ACarConfig.Cameras.PartsRimsBrandRear = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRimsBrandRear", DefaultCarConfig.Cameras.PartsRimsBrandRear);
		ACarConfig.Cameras.PartsRimsBrandAll = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRimsBrandAll", DefaultCarConfig.Cameras.PartsRimsBrandAll);
		ACarConfig.Cameras.PartsHoods = mINI_ReadVLTHash(CarINI, "Cameras", "PartsHoods", DefaultCarConfig.Cameras.PartsHoods);
		ACarConfig.Cameras.PartsRoofScoops = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRoofScoops", DefaultCarConfig.Cameras.PartsRoofScoops);
		ACarConfig.Cameras.PartsInterior = mINI_ReadVLTHash(CarINI, "Cameras", "PartsInterior", DefaultCarConfig.Cameras.PartsInterior);
		ACarConfig.Cameras.PartsRoof = mINI_ReadVLTHash(CarINI, "Cameras", "PartsRoof", DefaultCarConfig.Cameras.PartsRoof);
		ACarConfig.Cameras.PartsBrakes = mINI_ReadVLTHash(CarINI, "Cameras", "PartsBrakes", DefaultCarConfig.Cameras.PartsBrakes);
		ACarConfig.Cameras.PartsHeadlights = mINI_ReadVLTHash(CarINI, "Cameras", "PartsHeadlights", DefaultCarConfig.Cameras.PartsHeadlights);
		ACarConfig.Cameras.PartsTaillights = mINI_ReadVLTHash(CarINI, "Cameras", "PartsTaillights", DefaultCarConfig.Cameras.PartsTaillights);
		ACarConfig.Cameras.PartsMirrors = mINI_ReadVLTHash(CarINI, "Cameras", "PartsMirrors", DefaultCarConfig.Cameras.PartsMirrors);
		ACarConfig.Cameras.PartsAttachments = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachments", DefaultCarConfig.Cameras.PartsAttachments);
		ACarConfig.Cameras.PartsAttachment0 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment0", DefaultCarConfig.Cameras.PartsAttachment0);
		ACarConfig.Cameras.PartsAttachment1 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment1", DefaultCarConfig.Cameras.PartsAttachment1);
		ACarConfig.Cameras.PartsAttachment2 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment2", DefaultCarConfig.Cameras.PartsAttachment2);
		ACarConfig.Cameras.PartsAttachment3 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment3", DefaultCarConfig.Cameras.PartsAttachment3);
		ACarConfig.Cameras.PartsAttachment4 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment4", DefaultCarConfig.Cameras.PartsAttachment4);
		ACarConfig.Cameras.PartsAttachment5 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment5", DefaultCarConfig.Cameras.PartsAttachment5);
		ACarConfig.Cameras.PartsAttachment6 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment6", DefaultCarConfig.Cameras.PartsAttachment6);
		ACarConfig.Cameras.PartsAttachment7 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment7", DefaultCarConfig.Cameras.PartsAttachment7);
		ACarConfig.Cameras.PartsAttachment8 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment8", DefaultCarConfig.Cameras.PartsAttachment8);
		ACarConfig.Cameras.PartsAttachment9 = mINI_ReadVLTHash(CarINI, "Cameras", "PartsAttachment9", DefaultCarConfig.Cameras.PartsAttachment9);
		ACarConfig.Cameras.VisualPaint = mINI_ReadVLTHash(CarINI, "Cameras", "VisualPaint", DefaultCarConfig.Cameras.VisualPaint);
		ACarConfig.Cameras.VisualVinyls = mINI_ReadVLTHash(CarINI, "Cameras", "VisualVinyls", DefaultCarConfig.Cameras.VisualVinyls);
		ACarConfig.Cameras.VisualVinylsGroup = mINI_ReadVLTHash(CarINI, "Cameras", "VisualVinylsGroup", DefaultCarConfig.Cameras.VisualVinylsGroup);
		ACarConfig.Cameras.VisualRimPaint = mINI_ReadVLTHash(CarINI, "Cameras", "VisualRimPaint", DefaultCarConfig.Cameras.VisualRimPaint);
		ACarConfig.Cameras.VisualWindowTint = mINI_ReadVLTHash(CarINI, "Cameras", "VisualWindowTint", DefaultCarConfig.Cameras.VisualWindowTint);
		ACarConfig.Cameras.VisualDecals = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecals", DefaultCarConfig.Cameras.VisualDecals);
		ACarConfig.Cameras.VisualDecalsWindshield = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield", DefaultCarConfig.Cameras.VisualDecalsWindshield);
		ACarConfig.Cameras.VisualDecalsWindshield1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield1", DefaultCarConfig.Cameras.VisualDecalsWindshield1);
		ACarConfig.Cameras.VisualDecalsWindshield2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield2", DefaultCarConfig.Cameras.VisualDecalsWindshield2);
		ACarConfig.Cameras.VisualDecalsWindshield3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield3", DefaultCarConfig.Cameras.VisualDecalsWindshield3);
		ACarConfig.Cameras.VisualDecalsWindshield4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield4", DefaultCarConfig.Cameras.VisualDecalsWindshield4);
		ACarConfig.Cameras.VisualDecalsWindshield5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield5", DefaultCarConfig.Cameras.VisualDecalsWindshield5);
		ACarConfig.Cameras.VisualDecalsWindshield6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield6", DefaultCarConfig.Cameras.VisualDecalsWindshield6);
		ACarConfig.Cameras.VisualDecalsWindshield7 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield7", DefaultCarConfig.Cameras.VisualDecalsWindshield7);
		ACarConfig.Cameras.VisualDecalsWindshield8 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsWindshield8", DefaultCarConfig.Cameras.VisualDecalsWindshield8);
		ACarConfig.Cameras.VisualDecalsRearWindow = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow", DefaultCarConfig.Cameras.VisualDecalsRearWindow);
		ACarConfig.Cameras.VisualDecalsRearWindow1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow1", DefaultCarConfig.Cameras.VisualDecalsRearWindow1);
		ACarConfig.Cameras.VisualDecalsRearWindow2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow2", DefaultCarConfig.Cameras.VisualDecalsRearWindow2);
		ACarConfig.Cameras.VisualDecalsRearWindow3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow3", DefaultCarConfig.Cameras.VisualDecalsRearWindow3);
		ACarConfig.Cameras.VisualDecalsRearWindow4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow4", DefaultCarConfig.Cameras.VisualDecalsRearWindow4);
		ACarConfig.Cameras.VisualDecalsRearWindow5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow5", DefaultCarConfig.Cameras.VisualDecalsRearWindow5);
		ACarConfig.Cameras.VisualDecalsRearWindow6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow6", DefaultCarConfig.Cameras.VisualDecalsRearWindow6);
		ACarConfig.Cameras.VisualDecalsRearWindow7 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow7", DefaultCarConfig.Cameras.VisualDecalsRearWindow7);
		ACarConfig.Cameras.VisualDecalsRearWindow8 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRearWindow8", DefaultCarConfig.Cameras.VisualDecalsRearWindow8);
		ACarConfig.Cameras.VisualDecalsLeftDoor = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor", DefaultCarConfig.Cameras.VisualDecalsLeftDoor);
		ACarConfig.Cameras.VisualDecalsLeftDoor1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor1", DefaultCarConfig.Cameras.VisualDecalsLeftDoor1);
		ACarConfig.Cameras.VisualDecalsLeftDoor2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor2", DefaultCarConfig.Cameras.VisualDecalsLeftDoor2);
		ACarConfig.Cameras.VisualDecalsLeftDoor3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor3", DefaultCarConfig.Cameras.VisualDecalsLeftDoor3);
		ACarConfig.Cameras.VisualDecalsLeftDoor4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor4", DefaultCarConfig.Cameras.VisualDecalsLeftDoor4);
		ACarConfig.Cameras.VisualDecalsLeftDoor5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor5", DefaultCarConfig.Cameras.VisualDecalsLeftDoor5);
		ACarConfig.Cameras.VisualDecalsLeftDoor6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftDoor6", DefaultCarConfig.Cameras.VisualDecalsLeftDoor6);
		ACarConfig.Cameras.VisualDecalsRightDoor = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor", DefaultCarConfig.Cameras.VisualDecalsRightDoor);
		ACarConfig.Cameras.VisualDecalsRightDoor1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor1", DefaultCarConfig.Cameras.VisualDecalsRightDoor1);
		ACarConfig.Cameras.VisualDecalsRightDoor2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor2", DefaultCarConfig.Cameras.VisualDecalsRightDoor2);
		ACarConfig.Cameras.VisualDecalsRightDoor3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor3", DefaultCarConfig.Cameras.VisualDecalsRightDoor3);
		ACarConfig.Cameras.VisualDecalsRightDoor4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor4", DefaultCarConfig.Cameras.VisualDecalsRightDoor4);
		ACarConfig.Cameras.VisualDecalsRightDoor5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor5", DefaultCarConfig.Cameras.VisualDecalsRightDoor5);
		ACarConfig.Cameras.VisualDecalsRightDoor6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightDoor6", DefaultCarConfig.Cameras.VisualDecalsRightDoor6);
		ACarConfig.Cameras.VisualDecalsLeftQuarter = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter);
		ACarConfig.Cameras.VisualDecalsLeftQuarter1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter1", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter1);
		ACarConfig.Cameras.VisualDecalsLeftQuarter2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter2", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter2);
		ACarConfig.Cameras.VisualDecalsLeftQuarter3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter3", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter3);
		ACarConfig.Cameras.VisualDecalsLeftQuarter4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter4", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter4);
		ACarConfig.Cameras.VisualDecalsLeftQuarter5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter5", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter5);
		ACarConfig.Cameras.VisualDecalsLeftQuarter6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter6", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter6);
		ACarConfig.Cameras.VisualDecalsLeftQuarter7 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter7", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter7);
		ACarConfig.Cameras.VisualDecalsLeftQuarter8 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsLeftQuarter8", DefaultCarConfig.Cameras.VisualDecalsLeftQuarter8);
		ACarConfig.Cameras.VisualDecalsRightQuarter = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter", DefaultCarConfig.Cameras.VisualDecalsRightQuarter);
		ACarConfig.Cameras.VisualDecalsRightQuarter1 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter1", DefaultCarConfig.Cameras.VisualDecalsRightQuarter1);
		ACarConfig.Cameras.VisualDecalsRightQuarter2 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter2", DefaultCarConfig.Cameras.VisualDecalsRightQuarter2);
		ACarConfig.Cameras.VisualDecalsRightQuarter3 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter3", DefaultCarConfig.Cameras.VisualDecalsRightQuarter3);
		ACarConfig.Cameras.VisualDecalsRightQuarter4 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter4", DefaultCarConfig.Cameras.VisualDecalsRightQuarter4);
		ACarConfig.Cameras.VisualDecalsRightQuarter5 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter5", DefaultCarConfig.Cameras.VisualDecalsRightQuarter5);
		ACarConfig.Cameras.VisualDecalsRightQuarter6 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter6", DefaultCarConfig.Cameras.VisualDecalsRightQuarter6);
		ACarConfig.Cameras.VisualDecalsRightQuarter7 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter7", DefaultCarConfig.Cameras.VisualDecalsRightQuarter7);
		ACarConfig.Cameras.VisualDecalsRightQuarter8 = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDecalsRightQuarter8", DefaultCarConfig.Cameras.VisualDecalsRightQuarter8);
		ACarConfig.Cameras.VisualNumbers = mINI_ReadVLTHash(CarINI, "Cameras", "VisualNumbers", DefaultCarConfig.Cameras.VisualNumbers);
		ACarConfig.Cameras.VisualCustomGauges = mINI_ReadVLTHash(CarINI, "Cameras", "VisualCustomGauges", DefaultCarConfig.Cameras.VisualCustomGauges);
		ACarConfig.Cameras.VisualDriver = mINI_ReadVLTHash(CarINI, "Cameras", "VisualDriver", DefaultCarConfig.Cameras.VisualDriver);
		ACarConfig.Cameras.VisualLicensePlate = mINI_ReadVLTHash(CarINI, "Cameras", "VisualLicensePlate", DefaultCarConfig.Cameras.VisualLicensePlate);
		ACarConfig.Cameras.VisualTires = mINI_ReadVLTHash(CarINI, "Cameras", "VisualTires", DefaultCarConfig.Cameras.VisualTires);
		ACarConfig.Cameras.VisualNeon = mINI_ReadVLTHash(CarINI, "Cameras", "VisualNeon", DefaultCarConfig.Cameras.VisualNeon);

		// StockParts
		ACarConfig.StockParts.CustomStockParts = mINI_ReadInteger(CarINI, "StockParts", "CustomStockParts", DefaultCarConfig.StockParts.CustomStockParts) != 0;
		for (int p = 0; p < NumCarSlots; p++) ACarConfig.StockParts.Parts[p] = DefaultCarConfig.StockParts.Parts[p];

		ACarConfig.StockParts.Parts[23] = mINI_ReadHash(CarINI, "StockParts", "BodyKits", DefaultCarConfig.StockParts.Parts[23]);
		ACarConfig.StockParts.Parts[44] = mINI_ReadHash(CarINI, "StockParts", "Spoilers", DefaultCarConfig.StockParts.Parts[44]);
		ACarConfig.StockParts.Parts[66] = mINI_ReadHash(CarINI, "StockParts", "RimsFront", DefaultCarConfig.StockParts.Parts[66]);
		ACarConfig.StockParts.Parts[67] = mINI_ReadHash(CarINI, "StockParts", "RimsRear", DefaultCarConfig.StockParts.Parts[67]);
		ACarConfig.StockParts.Parts[63] = mINI_ReadHash(CarINI, "StockParts", "Hoods", DefaultCarConfig.StockParts.Parts[63]);
		ACarConfig.StockParts.Parts[62] = mINI_ReadHash(CarINI, "StockParts", "RoofScoops", DefaultCarConfig.StockParts.Parts[62]);
		ACarConfig.StockParts.Parts[28] = mINI_ReadHash(CarINI, "StockParts", "Interior", DefaultCarConfig.StockParts.Parts[28]);
		ACarConfig.StockParts.Parts[0] = mINI_ReadHash(CarINI, "StockParts", "Roof", DefaultCarConfig.StockParts.Parts[0]);
		ACarConfig.StockParts.Parts[24] = mINI_ReadHash(CarINI, "StockParts", "Brakes", DefaultCarConfig.StockParts.Parts[24]);
		ACarConfig.StockParts.Parts[31] = mINI_ReadHash(CarINI, "StockParts", "Headlights", DefaultCarConfig.StockParts.Parts[31]);
		ACarConfig.StockParts.Parts[29] = mINI_ReadHash(CarINI, "StockParts", "Taillights", DefaultCarConfig.StockParts.Parts[29]);
		ACarConfig.StockParts.Parts[33] = mINI_ReadHash(CarINI, "StockParts", "Mirrors", DefaultCarConfig.StockParts.Parts[33]);
		ACarConfig.StockParts.Parts[52] = mINI_ReadHash(CarINI, "StockParts", "Attachment0", DefaultCarConfig.StockParts.Parts[52]);
		ACarConfig.StockParts.Parts[53] = mINI_ReadHash(CarINI, "StockParts", "Attachment1", DefaultCarConfig.StockParts.Parts[53]);
		ACarConfig.StockParts.Parts[54] = mINI_ReadHash(CarINI, "StockParts", "Attachment2", DefaultCarConfig.StockParts.Parts[54]);
		ACarConfig.StockParts.Parts[55] = mINI_ReadHash(CarINI, "StockParts", "Attachment3", DefaultCarConfig.StockParts.Parts[55]);
		ACarConfig.StockParts.Parts[56] = mINI_ReadHash(CarINI, "StockParts", "Attachment4", DefaultCarConfig.StockParts.Parts[56]);
		ACarConfig.StockParts.Parts[57] = mINI_ReadHash(CarINI, "StockParts", "Attachment5", DefaultCarConfig.StockParts.Parts[57]);
		ACarConfig.StockParts.Parts[58] = mINI_ReadHash(CarINI, "StockParts", "Attachment6", DefaultCarConfig.StockParts.Parts[58]);
		ACarConfig.StockParts.Parts[59] = mINI_ReadHash(CarINI, "StockParts", "Attachment7", DefaultCarConfig.StockParts.Parts[59]);
		ACarConfig.StockParts.Parts[60] = mINI_ReadHash(CarINI, "StockParts", "Attachment8", DefaultCarConfig.StockParts.Parts[60]);
		ACarConfig.StockParts.Parts[61] = mINI_ReadHash(CarINI, "StockParts", "Attachment9", DefaultCarConfig.StockParts.Parts[61]);
		ACarConfig.StockParts.Parts[76] = mINI_ReadHash(CarINI, "StockParts", "Paint", DefaultCarConfig.StockParts.Parts[76]);
		ACarConfig.StockParts.Parts[77] = mINI_ReadHash(CarINI, "StockParts", "Vinyls", DefaultCarConfig.StockParts.Parts[77]);
		ACarConfig.StockParts.Parts[79] = mINI_ReadHash(CarINI, "StockParts", "VinylColor1", DefaultCarConfig.StockParts.Parts[79]);
		ACarConfig.StockParts.Parts[80] = mINI_ReadHash(CarINI, "StockParts", "VinylColor2", DefaultCarConfig.StockParts.Parts[80]);
		ACarConfig.StockParts.Parts[81] = mINI_ReadHash(CarINI, "StockParts", "VinylColor3", DefaultCarConfig.StockParts.Parts[81]);
		ACarConfig.StockParts.Parts[82] = mINI_ReadHash(CarINI, "StockParts", "VinylColor4", DefaultCarConfig.StockParts.Parts[82]);
		ACarConfig.StockParts.Parts[78] = mINI_ReadHash(CarINI, "StockParts", "RimPaint", DefaultCarConfig.StockParts.Parts[78]);
		ACarConfig.StockParts.Parts[131] = mINI_ReadHash(CarINI, "StockParts", "WindowTint", DefaultCarConfig.StockParts.Parts[131]);
		ACarConfig.StockParts.Parts[83] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield1", DefaultCarConfig.StockParts.Parts[83]);
		ACarConfig.StockParts.Parts[84] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield2", DefaultCarConfig.StockParts.Parts[84]);
		ACarConfig.StockParts.Parts[85] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield3", DefaultCarConfig.StockParts.Parts[85]);
		ACarConfig.StockParts.Parts[86] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield4", DefaultCarConfig.StockParts.Parts[86]);
		ACarConfig.StockParts.Parts[87] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield5", DefaultCarConfig.StockParts.Parts[87]);
		ACarConfig.StockParts.Parts[88] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield6", DefaultCarConfig.StockParts.Parts[88]);
		ACarConfig.StockParts.Parts[89] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield7", DefaultCarConfig.StockParts.Parts[89]);
		ACarConfig.StockParts.Parts[90] = mINI_ReadHash(CarINI, "StockParts", "DecalsWindshield8", DefaultCarConfig.StockParts.Parts[90]);
		ACarConfig.StockParts.Parts[91] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow1", DefaultCarConfig.StockParts.Parts[91]);
		ACarConfig.StockParts.Parts[92] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow2", DefaultCarConfig.StockParts.Parts[92]);
		ACarConfig.StockParts.Parts[93] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow3", DefaultCarConfig.StockParts.Parts[93]);
		ACarConfig.StockParts.Parts[94] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow4", DefaultCarConfig.StockParts.Parts[94]);
		ACarConfig.StockParts.Parts[95] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow5", DefaultCarConfig.StockParts.Parts[95]);
		ACarConfig.StockParts.Parts[96] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow6", DefaultCarConfig.StockParts.Parts[96]);
		ACarConfig.StockParts.Parts[97] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow7", DefaultCarConfig.StockParts.Parts[97]);
		ACarConfig.StockParts.Parts[98] = mINI_ReadHash(CarINI, "StockParts", "DecalsRearWindow8", DefaultCarConfig.StockParts.Parts[98]);
		ACarConfig.StockParts.Parts[99] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor1", DefaultCarConfig.StockParts.Parts[99]);
		ACarConfig.StockParts.Parts[100] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor2", DefaultCarConfig.StockParts.Parts[100]);
		ACarConfig.StockParts.Parts[101] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor3", DefaultCarConfig.StockParts.Parts[101]);
		ACarConfig.StockParts.Parts[102] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor4", DefaultCarConfig.StockParts.Parts[102]);
		ACarConfig.StockParts.Parts[103] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor5", DefaultCarConfig.StockParts.Parts[103]);
		ACarConfig.StockParts.Parts[104] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftDoor6", DefaultCarConfig.StockParts.Parts[104]);
		ACarConfig.StockParts.Parts[107] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor1", DefaultCarConfig.StockParts.Parts[107]);
		ACarConfig.StockParts.Parts[108] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor2", DefaultCarConfig.StockParts.Parts[108]);
		ACarConfig.StockParts.Parts[109] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor3", DefaultCarConfig.StockParts.Parts[109]);
		ACarConfig.StockParts.Parts[110] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor4", DefaultCarConfig.StockParts.Parts[110]);
		ACarConfig.StockParts.Parts[111] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor5", DefaultCarConfig.StockParts.Parts[111]);
		ACarConfig.StockParts.Parts[112] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightDoor6", DefaultCarConfig.StockParts.Parts[112]);
		ACarConfig.StockParts.Parts[115] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter1", DefaultCarConfig.StockParts.Parts[115]);
		ACarConfig.StockParts.Parts[116] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter2", DefaultCarConfig.StockParts.Parts[116]);
		ACarConfig.StockParts.Parts[117] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter3", DefaultCarConfig.StockParts.Parts[117]);
		ACarConfig.StockParts.Parts[118] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter4", DefaultCarConfig.StockParts.Parts[118]);
		ACarConfig.StockParts.Parts[119] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter5", DefaultCarConfig.StockParts.Parts[119]);
		ACarConfig.StockParts.Parts[120] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter6", DefaultCarConfig.StockParts.Parts[120]);
		ACarConfig.StockParts.Parts[121] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter7", DefaultCarConfig.StockParts.Parts[121]);
		ACarConfig.StockParts.Parts[122] = mINI_ReadHash(CarINI, "StockParts", "DecalsLeftQuarter8", DefaultCarConfig.StockParts.Parts[122]);
		ACarConfig.StockParts.Parts[123] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter1", DefaultCarConfig.StockParts.Parts[123]);
		ACarConfig.StockParts.Parts[124] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter2", DefaultCarConfig.StockParts.Parts[124]);
		ACarConfig.StockParts.Parts[125] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter3", DefaultCarConfig.StockParts.Parts[125]);
		ACarConfig.StockParts.Parts[126] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter4", DefaultCarConfig.StockParts.Parts[126]);
		ACarConfig.StockParts.Parts[127] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter5", DefaultCarConfig.StockParts.Parts[127]);
		ACarConfig.StockParts.Parts[128] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter6", DefaultCarConfig.StockParts.Parts[128]);
		ACarConfig.StockParts.Parts[129] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter7", DefaultCarConfig.StockParts.Parts[129]);
		ACarConfig.StockParts.Parts[130] = mINI_ReadHash(CarINI, "StockParts", "DecalsRightQuarter8", DefaultCarConfig.StockParts.Parts[130]);
		ACarConfig.StockParts.Parts[105] = mINI_ReadHash(CarINI, "StockParts", "NumbersLeftL", DefaultCarConfig.StockParts.Parts[105]);
		ACarConfig.StockParts.Parts[106] = mINI_ReadHash(CarINI, "StockParts", "NumbersLeftR", DefaultCarConfig.StockParts.Parts[106]);
		ACarConfig.StockParts.Parts[113] = mINI_ReadHash(CarINI, "StockParts", "NumbersRightL", DefaultCarConfig.StockParts.Parts[113]);
		ACarConfig.StockParts.Parts[114] = mINI_ReadHash(CarINI, "StockParts", "NumbersRightR", DefaultCarConfig.StockParts.Parts[114]);
		ACarConfig.StockParts.Parts[132] = mINI_ReadHash(CarINI, "StockParts", "CustomGauges", DefaultCarConfig.StockParts.Parts[132]);
		ACarConfig.StockParts.Parts[133] = mINI_ReadHash(CarINI, "StockParts", "CustomGaugesBackingColor", DefaultCarConfig.StockParts.Parts[133]);
		ACarConfig.StockParts.Parts[134] = mINI_ReadHash(CarINI, "StockParts", "CustomGaugesNeedleColor", DefaultCarConfig.StockParts.Parts[134]);
		ACarConfig.StockParts.Parts[135] = mINI_ReadHash(CarINI, "StockParts", "CustomGaugesCharacterColor", DefaultCarConfig.StockParts.Parts[135]);
		ACarConfig.StockParts.Parts[43] = mINI_ReadHash(CarINI, "StockParts", "Driver", DefaultCarConfig.StockParts.Parts[43]);
		ACarConfig.StockParts.Parts[69] = mINI_ReadHash(CarINI, "StockParts", "LicensePlate", DefaultCarConfig.StockParts.Parts[69]);
		ACarConfig.StockParts.Parts[64] = mINI_ReadHash(CarINI, "StockParts", "Tires", DefaultCarConfig.StockParts.Parts[64]);
		ACarConfig.StockParts.Parts[65] = mINI_ReadHash(CarINI, "StockParts", "Neon", DefaultCarConfig.StockParts.Parts[65]);

		// RandomParts
		ACarConfig.RandomParts.ForceCustomizationLevel = mINI_ReadInteger(CarINI, "RandomParts", "ForceCustomizationLevel", DefaultCarConfig.RandomParts.ForceCustomizationLevel);
		ACarConfig.RandomParts.CustomRandomParts = mINI_ReadInteger(CarINI, "RandomParts", "CustomRandomParts", DefaultCarConfig.RandomParts.CustomRandomParts) != 0;
		ACarConfig.RandomParts.RandomizeInTraffic = mINI_ReadInteger(CarINI, "RandomParts", "RandomizeInTraffic", DefaultCarConfig.RandomParts.RandomizeInTraffic) != 0;

		if (RandomizeTraffic && ACarConfig.RandomParts.RandomizeInTraffic) SetSkinnable(i);

		for (int p = 0; p < NumCarSlots; p++) ACarConfig.RandomParts.Parts[p] = DefaultCarConfig.RandomParts.Parts[p];

		ACarConfig.RandomParts.Parts[23] = mINI_ReadInteger(CarINI, "RandomParts", "BodyKits", DefaultCarConfig.RandomParts.Parts[23]) != 0;
		ACarConfig.RandomParts.Parts[44] = mINI_ReadInteger(CarINI, "RandomParts", "Spoilers", DefaultCarConfig.RandomParts.Parts[44]) != 0;
		ACarConfig.RandomParts.Parts[66] = mINI_ReadInteger(CarINI, "RandomParts", "RimsFront", DefaultCarConfig.RandomParts.Parts[66]) != 0;
		ACarConfig.RandomParts.Parts[67] = mINI_ReadInteger(CarINI, "RandomParts", "RimsRear", DefaultCarConfig.RandomParts.Parts[67]) != 0;
		ACarConfig.RandomParts.Parts[63] = mINI_ReadInteger(CarINI, "RandomParts", "Hoods", DefaultCarConfig.RandomParts.Parts[63]) != 0;
		ACarConfig.RandomParts.Parts[62] = mINI_ReadInteger(CarINI, "RandomParts", "RoofScoops", DefaultCarConfig.RandomParts.Parts[62]) != 0;
		ACarConfig.RandomParts.Parts[28] = mINI_ReadInteger(CarINI, "RandomParts", "Interior", DefaultCarConfig.RandomParts.Parts[28]) != 0;
		ACarConfig.RandomParts.Parts[0] = mINI_ReadInteger(CarINI, "RandomParts", "Roof", DefaultCarConfig.RandomParts.Parts[0]) != 0;
		ACarConfig.RandomParts.Parts[24] = mINI_ReadInteger(CarINI, "RandomParts", "Brakes", DefaultCarConfig.RandomParts.Parts[24]) != 0;
		ACarConfig.RandomParts.Parts[31] = mINI_ReadInteger(CarINI, "RandomParts", "Headlights", DefaultCarConfig.RandomParts.Parts[31]) != 0;
		ACarConfig.RandomParts.Parts[29] = mINI_ReadInteger(CarINI, "RandomParts", "Taillights", DefaultCarConfig.RandomParts.Parts[29]) != 0;
		ACarConfig.RandomParts.Parts[33] = mINI_ReadInteger(CarINI, "RandomParts", "Mirrors", DefaultCarConfig.RandomParts.Parts[33]) != 0;
		ACarConfig.RandomParts.Parts[52] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment0", DefaultCarConfig.RandomParts.Parts[52]) != 0;
		ACarConfig.RandomParts.Parts[53] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment1", DefaultCarConfig.RandomParts.Parts[53]) != 0;
		ACarConfig.RandomParts.Parts[54] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment2", DefaultCarConfig.RandomParts.Parts[54]) != 0;
		ACarConfig.RandomParts.Parts[55] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment3", DefaultCarConfig.RandomParts.Parts[55]) != 0;
		ACarConfig.RandomParts.Parts[56] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment4", DefaultCarConfig.RandomParts.Parts[56]) != 0;
		ACarConfig.RandomParts.Parts[57] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment5", DefaultCarConfig.RandomParts.Parts[57]) != 0;
		ACarConfig.RandomParts.Parts[58] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment6", DefaultCarConfig.RandomParts.Parts[58]) != 0;
		ACarConfig.RandomParts.Parts[59] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment7", DefaultCarConfig.RandomParts.Parts[59]) != 0;
		ACarConfig.RandomParts.Parts[60] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment8", DefaultCarConfig.RandomParts.Parts[60]) != 0;
		ACarConfig.RandomParts.Parts[61] = mINI_ReadInteger(CarINI, "RandomParts", "Attachment9", DefaultCarConfig.RandomParts.Parts[61]) != 0;
		ACarConfig.RandomParts.Parts[76] = mINI_ReadInteger(CarINI, "RandomParts", "Paint", DefaultCarConfig.RandomParts.Parts[76]) != 0;
		ACarConfig.RandomParts.Parts[77] = mINI_ReadInteger(CarINI, "RandomParts", "Vinyls", DefaultCarConfig.RandomParts.Parts[77]) != 0;
		ACarConfig.RandomParts.Parts[79] = mINI_ReadInteger(CarINI, "RandomParts", "VinylColor1", DefaultCarConfig.RandomParts.Parts[79]) != 0;
		ACarConfig.RandomParts.Parts[80] = mINI_ReadInteger(CarINI, "RandomParts", "VinylColor2", DefaultCarConfig.RandomParts.Parts[80]) != 0;
		ACarConfig.RandomParts.Parts[81] = mINI_ReadInteger(CarINI, "RandomParts", "VinylColor3", DefaultCarConfig.RandomParts.Parts[81]) != 0;
		ACarConfig.RandomParts.Parts[82] = mINI_ReadInteger(CarINI, "RandomParts", "VinylColor4", DefaultCarConfig.RandomParts.Parts[82]) != 0;
		ACarConfig.RandomParts.Parts[78] = mINI_ReadInteger(CarINI, "RandomParts", "RimPaint", DefaultCarConfig.RandomParts.Parts[78]) != 0;
		ACarConfig.RandomParts.Parts[131] = mINI_ReadInteger(CarINI, "RandomParts", "WindowTint", DefaultCarConfig.RandomParts.Parts[131]) != 0;
		ACarConfig.RandomParts.Parts[83] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield1", DefaultCarConfig.RandomParts.Parts[83]) != 0;
		ACarConfig.RandomParts.Parts[84] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield2", DefaultCarConfig.RandomParts.Parts[84]) != 0;
		ACarConfig.RandomParts.Parts[85] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield3", DefaultCarConfig.RandomParts.Parts[85]) != 0;
		ACarConfig.RandomParts.Parts[86] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield4", DefaultCarConfig.RandomParts.Parts[86]) != 0;
		ACarConfig.RandomParts.Parts[87] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield5", DefaultCarConfig.RandomParts.Parts[87]) != 0;
		ACarConfig.RandomParts.Parts[88] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield6", DefaultCarConfig.RandomParts.Parts[88]) != 0;
		ACarConfig.RandomParts.Parts[89] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield7", DefaultCarConfig.RandomParts.Parts[89]) != 0;
		ACarConfig.RandomParts.Parts[90] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsWindshield8", DefaultCarConfig.RandomParts.Parts[90]) != 0;
		ACarConfig.RandomParts.Parts[91] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow1", DefaultCarConfig.RandomParts.Parts[91]) != 0;
		ACarConfig.RandomParts.Parts[92] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow2", DefaultCarConfig.RandomParts.Parts[92]) != 0;
		ACarConfig.RandomParts.Parts[93] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow3", DefaultCarConfig.RandomParts.Parts[93]) != 0;
		ACarConfig.RandomParts.Parts[94] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow4", DefaultCarConfig.RandomParts.Parts[94]) != 0;
		ACarConfig.RandomParts.Parts[95] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow5", DefaultCarConfig.RandomParts.Parts[95]) != 0;
		ACarConfig.RandomParts.Parts[96] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow6", DefaultCarConfig.RandomParts.Parts[96]) != 0;
		ACarConfig.RandomParts.Parts[97] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow7", DefaultCarConfig.RandomParts.Parts[97]) != 0;
		ACarConfig.RandomParts.Parts[98] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRearWindow8", DefaultCarConfig.RandomParts.Parts[98]) != 0;
		ACarConfig.RandomParts.Parts[99] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor1", DefaultCarConfig.RandomParts.Parts[99]) != 0;
		ACarConfig.RandomParts.Parts[100] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor2", DefaultCarConfig.RandomParts.Parts[100]) != 0;
		ACarConfig.RandomParts.Parts[101] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor3", DefaultCarConfig.RandomParts.Parts[101]) != 0;
		ACarConfig.RandomParts.Parts[102] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor4", DefaultCarConfig.RandomParts.Parts[102]) != 0;
		ACarConfig.RandomParts.Parts[103] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor5", DefaultCarConfig.RandomParts.Parts[103]) != 0;
		ACarConfig.RandomParts.Parts[104] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftDoor6", DefaultCarConfig.RandomParts.Parts[104]) != 0;
		ACarConfig.RandomParts.Parts[107] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor1", DefaultCarConfig.RandomParts.Parts[107]) != 0;
		ACarConfig.RandomParts.Parts[108] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor2", DefaultCarConfig.RandomParts.Parts[108]) != 0;
		ACarConfig.RandomParts.Parts[109] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor3", DefaultCarConfig.RandomParts.Parts[109]) != 0;
		ACarConfig.RandomParts.Parts[110] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor4", DefaultCarConfig.RandomParts.Parts[110]) != 0;
		ACarConfig.RandomParts.Parts[111] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor5", DefaultCarConfig.RandomParts.Parts[111]) != 0;
		ACarConfig.RandomParts.Parts[112] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightDoor6", DefaultCarConfig.RandomParts.Parts[112]) != 0;
		ACarConfig.RandomParts.Parts[115] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter1", DefaultCarConfig.RandomParts.Parts[115]) != 0;
		ACarConfig.RandomParts.Parts[116] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter2", DefaultCarConfig.RandomParts.Parts[116]) != 0;
		ACarConfig.RandomParts.Parts[117] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter3", DefaultCarConfig.RandomParts.Parts[117]) != 0;
		ACarConfig.RandomParts.Parts[118] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter4", DefaultCarConfig.RandomParts.Parts[118]) != 0;
		ACarConfig.RandomParts.Parts[119] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter5", DefaultCarConfig.RandomParts.Parts[119]) != 0;
		ACarConfig.RandomParts.Parts[120] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter6", DefaultCarConfig.RandomParts.Parts[120]) != 0;
		ACarConfig.RandomParts.Parts[121] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter7", DefaultCarConfig.RandomParts.Parts[121]) != 0;
		ACarConfig.RandomParts.Parts[122] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsLeftQuarter8", DefaultCarConfig.RandomParts.Parts[122]) != 0;
		ACarConfig.RandomParts.Parts[123] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter1", DefaultCarConfig.RandomParts.Parts[123]) != 0;
		ACarConfig.RandomParts.Parts[124] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter2", DefaultCarConfig.RandomParts.Parts[124]) != 0;
		ACarConfig.RandomParts.Parts[125] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter3", DefaultCarConfig.RandomParts.Parts[125]) != 0;
		ACarConfig.RandomParts.Parts[126] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter4", DefaultCarConfig.RandomParts.Parts[126]) != 0;
		ACarConfig.RandomParts.Parts[127] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter5", DefaultCarConfig.RandomParts.Parts[127]) != 0;
		ACarConfig.RandomParts.Parts[128] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter6", DefaultCarConfig.RandomParts.Parts[128]) != 0;
		ACarConfig.RandomParts.Parts[129] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter7", DefaultCarConfig.RandomParts.Parts[129]) != 0;
		ACarConfig.RandomParts.Parts[130] = mINI_ReadInteger(CarINI, "RandomParts", "DecalsRightQuarter8", DefaultCarConfig.RandomParts.Parts[130]) != 0;
		ACarConfig.RandomParts.Parts[105] = mINI_ReadInteger(CarINI, "RandomParts", "NumbersLeftL", DefaultCarConfig.RandomParts.Parts[105]) != 0;
		ACarConfig.RandomParts.Parts[106] = mINI_ReadInteger(CarINI, "RandomParts", "NumbersLeftR", DefaultCarConfig.RandomParts.Parts[106]) != 0;
		ACarConfig.RandomParts.Parts[113] = mINI_ReadInteger(CarINI, "RandomParts", "NumbersRightL", DefaultCarConfig.RandomParts.Parts[113]) != 0;
		ACarConfig.RandomParts.Parts[114] = mINI_ReadInteger(CarINI, "RandomParts", "NumbersRightR", DefaultCarConfig.RandomParts.Parts[114]) != 0;
		ACarConfig.RandomParts.Parts[132] = mINI_ReadInteger(CarINI, "RandomParts", "CustomGauges", DefaultCarConfig.RandomParts.Parts[132]) != 0;
		ACarConfig.RandomParts.Parts[133] = mINI_ReadInteger(CarINI, "RandomParts", "CustomGaugesBackingColor", DefaultCarConfig.RandomParts.Parts[133]) != 0;
		ACarConfig.RandomParts.Parts[134] = mINI_ReadInteger(CarINI, "RandomParts", "CustomGaugesNeedleColor", DefaultCarConfig.RandomParts.Parts[134]) != 0;
		ACarConfig.RandomParts.Parts[135] = mINI_ReadInteger(CarINI, "RandomParts", "CustomGaugesCharacterColor", DefaultCarConfig.RandomParts.Parts[135]) != 0;
		ACarConfig.RandomParts.Parts[43] = mINI_ReadInteger(CarINI, "RandomParts", "Driver", DefaultCarConfig.RandomParts.Parts[43]) != 0;
		ACarConfig.RandomParts.Parts[69] = mINI_ReadInteger(CarINI, "RandomParts", "LicensePlate", DefaultCarConfig.RandomParts.Parts[69]) != 0;
		ACarConfig.RandomParts.Parts[64] = mINI_ReadInteger(CarINI, "RandomParts", "Tires", DefaultCarConfig.RandomParts.Parts[64]) != 0;
		ACarConfig.RandomParts.Parts[65] = mINI_ReadInteger(CarINI, "RandomParts", "Neon", DefaultCarConfig.RandomParts.Parts[65]) != 0;

		// FECooling
		ACarConfig.FECooling.BodyKits = mINI_ReadFloat(CarINI, "FECooling", "BodyKits", DefaultCarConfig.FECooling.BodyKits);
		ACarConfig.FECooling.Spoilers = mINI_ReadFloat(CarINI, "FECooling", "Spoilers", DefaultCarConfig.FECooling.Spoilers);
		ACarConfig.FECooling.Rims = mINI_ReadFloat(CarINI, "FECooling", "Rims", DefaultCarConfig.FECooling.Rims);
		ACarConfig.FECooling.Hoods = mINI_ReadFloat(CarINI, "FECooling", "Hoods", DefaultCarConfig.FECooling.Hoods);
		ACarConfig.FECooling.RoofScoops = mINI_ReadFloat(CarINI, "FECooling", "RoofScoops", DefaultCarConfig.FECooling.RoofScoops);
		ACarConfig.FECooling.Interior = mINI_ReadFloat(CarINI, "FECooling", "Interior", DefaultCarConfig.FECooling.Interior);
		ACarConfig.FECooling.Roof = mINI_ReadFloat(CarINI, "FECooling", "Roof", DefaultCarConfig.FECooling.Roof);
		ACarConfig.FECooling.Brakes = mINI_ReadFloat(CarINI, "FECooling", "Brakes", DefaultCarConfig.FECooling.Brakes);
		ACarConfig.FECooling.Headlights = mINI_ReadFloat(CarINI, "FECooling", "Headlights", DefaultCarConfig.FECooling.Headlights);
		ACarConfig.FECooling.Taillights = mINI_ReadFloat(CarINI, "FECooling", "Taillights", DefaultCarConfig.FECooling.Taillights);
		ACarConfig.FECooling.Mirrors = mINI_ReadFloat(CarINI, "FECooling", "Mirrors", DefaultCarConfig.FECooling.Mirrors);
		ACarConfig.FECooling.Attachment0 = mINI_ReadFloat(CarINI, "FECooling", "Attachment0", DefaultCarConfig.FECooling.Attachment0);
		ACarConfig.FECooling.Attachment1 = mINI_ReadFloat(CarINI, "FECooling", "Attachment1", DefaultCarConfig.FECooling.Attachment1);
		ACarConfig.FECooling.Attachment2 = mINI_ReadFloat(CarINI, "FECooling", "Attachment2", DefaultCarConfig.FECooling.Attachment2);
		ACarConfig.FECooling.Attachment3 = mINI_ReadFloat(CarINI, "FECooling", "Attachment3", DefaultCarConfig.FECooling.Attachment3);
		ACarConfig.FECooling.Attachment4 = mINI_ReadFloat(CarINI, "FECooling", "Attachment4", DefaultCarConfig.FECooling.Attachment4);
		ACarConfig.FECooling.Attachment5 = mINI_ReadFloat(CarINI, "FECooling", "Attachment5", DefaultCarConfig.FECooling.Attachment5);
		ACarConfig.FECooling.Attachment6 = mINI_ReadFloat(CarINI, "FECooling", "Attachment6", DefaultCarConfig.FECooling.Attachment6);
		ACarConfig.FECooling.Attachment7 = mINI_ReadFloat(CarINI, "FECooling", "Attachment7", DefaultCarConfig.FECooling.Attachment7);
		ACarConfig.FECooling.Attachment8 = mINI_ReadFloat(CarINI, "FECooling", "Attachment8", DefaultCarConfig.FECooling.Attachment8);
		ACarConfig.FECooling.Attachment9 = mINI_ReadFloat(CarINI, "FECooling", "Attachment9", DefaultCarConfig.FECooling.Attachment9);
		ACarConfig.FECooling.Paint = mINI_ReadFloat(CarINI, "FECooling", "Paint", DefaultCarConfig.FECooling.Paint);
		ACarConfig.FECooling.Vinyls = mINI_ReadFloat(CarINI, "FECooling", "Vinyls", DefaultCarConfig.FECooling.Vinyls);
		ACarConfig.FECooling.RimPaint = mINI_ReadFloat(CarINI, "FECooling", "RimPaint", DefaultCarConfig.FECooling.RimPaint);
		ACarConfig.FECooling.WindowTint = mINI_ReadFloat(CarINI, "FECooling", "WindowTint", DefaultCarConfig.FECooling.WindowTint);
		ACarConfig.FECooling.Decals = mINI_ReadFloat(CarINI, "FECooling", "Decals", DefaultCarConfig.FECooling.Decals);
		ACarConfig.FECooling.Driver = mINI_ReadFloat(CarINI, "FECooling", "Driver", DefaultCarConfig.FECooling.Driver);
		ACarConfig.FECooling.LicensePlate = mINI_ReadFloat(CarINI, "FECooling", "LicensePlate", DefaultCarConfig.FECooling.LicensePlate);
		ACarConfig.FECooling.Tires = mINI_ReadFloat(CarINI, "FECooling", "Tires", DefaultCarConfig.FECooling.Tires);
		ACarConfig.FECooling.Neon = mINI_ReadFloat(CarINI, "FECooling", "Neon", DefaultCarConfig.FECooling.Neon);


		CarConfigs_temp.push_back(ACarConfig); // Add to temp list
	}

	CarConfigs = std::move(CarConfigs_temp); // Replace global list with temp
}

void LoadFNGFixes()
{
	// Done in FEPackage.h instead
}

void LoadCopDestroyedStrings()
{
	CopDestroyedString ACopDestroyedString;
	std::vector<CopDestroyedString> CopDestroyedStrings_temp;

	auto CopDestroyedStringsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_CopDestroyedStrings.ini";
	mINI::INIFile CopDestroyedStringsINIFile(CopDestroyedStringsINIPath.string());
	mINI::INIStructure CopDestroyedStringsINI;
	CopDestroyedStringsINIFile.read(CopDestroyedStringsINI);

	char StringID[15];

	int NumCopDestroyedStrings = mINI_ReadInteger(CopDestroyedStringsINI, "CopDestroyedStrings", "NumberOfCopDestroyedStrings", DefaultCopDestroyedStringCount);

	for (int i = 0; i <= NumCopDestroyedStrings; i++)
	{
		sprintf(StringID, "String%d", i);

		ACopDestroyedString.PVehicle = mINI_ReadVLTHashS(CopDestroyedStringsINI, StringID, "PVehicle", GetDefaultCopDestroyedStringPVehicle(i));
		ACopDestroyedString.StringHash = mINI_ReadHashS(CopDestroyedStringsINI, StringID, "String", GetDefaultCopDestroyedString(i));

		CopDestroyedStrings_temp.push_back(ACopDestroyedString); // Add to temp list
	}

	CopDestroyedStrings = std::move(CopDestroyedStrings_temp); // Replace global list with temp
}

void LoadBonusCars()
{
	BonusCar ABonusCar;
	std::vector<BonusCar> BonusCars_temp;

	auto BonusCarsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_BonusCars.ini";
	mINI::INIFile BonusCarsINIFile(BonusCarsINIPath.string());
	mINI::INIStructure BonusCarsINI;
	BonusCarsINIFile.read(BonusCarsINI);

	char BonusCarNameBuf[16];

	int NumBonusCars = mINI_ReadInteger(BonusCarsINI, "BonusCars", "NumberOfBonusCars", -2);

	for (int i = -1; i <= NumBonusCars; i++)
	{
		sprintf(BonusCarNameBuf, "BonusCar%d", i);

		if (i == -1) // Directly modify the default value
		{
			sprintf(DefaultBonusCar.PresetName, mINI_ReadString(BonusCarsINI, BonusCarNameBuf, "PresetName", "M3GTRCAREERSTART"));
			DefaultBonusCar.CarRecordID = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "CarRecordID", 0x12345678);
			DefaultBonusCar.Category = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "Category", 0xF0020);
		}
		else
		{
			sprintf(ABonusCar.PresetName, mINI_ReadString(BonusCarsINI, BonusCarNameBuf, "PresetName", ""));
			ABonusCar.CarRecordID = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "CarRecordID", -1);
			ABonusCar.Category = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "Category", 0xF0008);
			ABonusCar.CEOnly = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "CEOnly", 0) != 0;
			ABonusCar.UnlockConditionType = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "UnlockConditionType", -1);
			ABonusCar.Blacklist = mINI_ReadInteger(BonusCarsINI, BonusCarNameBuf, "Blacklist", 15);
			ABonusCar.UnlockConditionStringHash = mINI_ReadHash(BonusCarsINI, BonusCarNameBuf, "UnlockConditionString");

			BonusCars_temp.push_back(ABonusCar); // Add to temp list
		}
	}

	BonusCars = std::move(BonusCars_temp); // Replace global list with temp

	if (NumBonusCars != -2)
	{
		// Use hooked bonus cars on new save games
		injector::MakeJMP(0x590D9F, FEPlayerCarDB_Default_BonusCarsCodeCave, true); // FEPlayerCarDB::Default

		// Hook unlockers to check for new bonus cars
		injector::MakeCALL(0x58AA63, UnlockSystem_IsBonusCarCEOnly, true); // UnlockSystem::IsCarUnlocked
		injector::MakeCALL(0x58ADB5, UnlockSystem_IsBonusCarCEOnly, true); // UnlockSystem::IsBonusCarAvailable

		// Hooks to get custom unlock conditions and texts from ini
		injector::MakeCALL(0x58A55C, QuickRaceUnlocker_IsCarUnlocked, true); // OnlineUnlocker::IsCarUnlocked
		injector::MakeCALL(0x58AA19, QuickRaceUnlocker_IsCarUnlocked, true); // UnlockSystem::IsCarUnlocked
		injector::MakeCALL(0x58AA47, QuickRaceUnlocker_IsCarUnlocked, true); // UnlockSystem::IsCarUnlocked
		injector::MakeCALL(0x7ADD80, UIQRCarSelect_GetBonusUnlockText, true); // UIQRCarSelect::RefreshHeader
		injector::MakeCALL(0x7ADD8D, UIQRCarSelect_GetBonusUnlockBinNumber, true); // UIQRCarSelect::RefreshHeader
	}
}

void LoadRimBrands()
{
	RimBrand ARimBrand;
	std::vector<RimBrand> RimBrands_temp;

	auto RimBrandsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_RimBrands.ini";
	mINI::INIFile RimBrandsINIFile(RimBrandsINIPath.string());
	mINI::INIStructure RimBrandsINI;
	RimBrandsINIFile.read(RimBrandsINI);

	char RimBrandID[15];

	int NumRimBrands = mINI_ReadInteger(RimBrandsINI, "RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);

	for (int i = 0; i <= NumRimBrands; i++)
	{
		sprintf(RimBrandID, "Brand%d", i);

		ARimBrand.BrandNameHash = mINI_ReadHashS(RimBrandsINI, RimBrandID, "BrandName", GetDefaultRimBrandName(i));
		ARimBrand.StringHash = mINI_ReadHashS(RimBrandsINI, RimBrandID, "String", GetDefaultRimBrandString(i));
		ARimBrand.TextureHash = mINI_ReadHashS(RimBrandsINI, RimBrandID, "Texture", GetDefaultRimBrandTexture(i));
		ARimBrand.NoRimSize = mINI_ReadInteger(RimBrandsINI, RimBrandID, "NoRimSize", i ? 0 : 1) != 0;

		RimBrands_temp.push_back(ARimBrand); // Add to temp list
	}

	RimBrands = std::move(RimBrands_temp); // Replace global list with temp

	NumRimBrands += 0x702;
	injector::WriteMemory<short>(0x7A587D, NumRimBrands, true); // TranslateCustomizeCatToMarker
	injector::WriteMemory<short>(0x7AFEAD, NumRimBrands, true); // GetMarkerNameFromCategory
	injector::WriteMemory<short>(0x7B6098, NumRimBrands, true); // CarCustomizeManager::GetUnlockHash
	injector::WriteMemory<short>(0x7BAD74, NumRimBrands, true); // CarCustomizeManager::IsCategoryLocked
	injector::WriteMemory<short>(0x7BAF96, NumRimBrands, true); // CarCustomizeManager::IsCategoryLocked
}

void LoadVinylGroups()
{
	VinylGroup AVinylGroup;
	std::vector<VinylGroup> VinylGroups_temp;

	auto VinylGroupsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_VinylGroups.ini";
	mINI::INIFile VinylGroupsINIFile(VinylGroupsINIPath.string());
	mINI::INIStructure VinylGroupsINI;
	VinylGroupsINIFile.read(VinylGroupsINI);

	char VinylBrandID[15];

	int NumVinylGroups = mINI_ReadInteger(VinylGroupsINI, "VinylGroups", "NumberOfVinylGroups", DefaultVinylGroupCount);

	for (int i = 0; i <= NumVinylGroups; i++)
	{
		sprintf(VinylBrandID, "Group%d", i);

		AVinylGroup.Index = mINI_ReadInteger(VinylGroupsINI, VinylBrandID, "Index", GetDefaultVinylGroupIndex(i));
		AVinylGroup.TextureHash = mINI_ReadHashS(VinylGroupsINI, VinylBrandID, "Texture", GetDefaultVinylGroupTexture(i));
		AVinylGroup.StringHash = mINI_ReadHashS(VinylGroupsINI, VinylBrandID, "String", GetDefaultVinylGroupString(i));
		AVinylGroup.UseAltCamera = mINI_ReadInteger(VinylGroupsINI, VinylBrandID, "UseAltCamera", GetDefaultVinylGroupAltCamera(i)) != 0;

		VinylGroups_temp.push_back(AVinylGroup); // Add to temp list
	}

	VinylGroups = std::move(VinylGroups_temp); // Replace global list with temp

	NumVinylGroups += 0x402;
	injector::WriteMemory<short>(0x7A5823, NumVinylGroups, true); // TranslateCustomizeCatToMarker
	injector::WriteMemory<short>(0x7AFE90, NumVinylGroups, true); // GetMarkerNameFromCategory
	injector::WriteMemory<short>(0x7B600C, NumVinylGroups, true); // CarCustomizeManager::GetUnlockHash
	injector::WriteMemory<short>(0x7BAEC3, NumVinylGroups, true); // CarCustomizeManager::IsCategoryLocked
	injector::WriteMemory<short>(0x7BAF10, NumVinylGroups, true); // CarCustomizeManager::IsCategoryLocked
	injector::WriteMemory<short>(0x7c0ae7, NumVinylGroups, true); // CustomizePaint::Setup
}

void LoadPaintGroups()
{
	PaintGroup APaintGroup;
	std::vector<PaintGroup> PaintGroups_temp;

	auto PaintGroupsINIPath = CurrentWorkingDirectory / "UnlimiterData" / "_PaintGroups.ini";
	mINI::INIFile PaintGroupsINIFile(PaintGroupsINIPath.string());
	mINI::INIStructure PaintGroupsINI;
	PaintGroupsINIFile.read(PaintGroupsINI);

	char PaintBrandID[15];

	int NumPaintGroups = mINI_ReadInteger(PaintGroupsINI, "PaintGroups", "NumberOfPaintGroups", DefaultPaintBrandCount);
	if (NumPaintGroups > MaximumPaintBrandCount) NumPaintGroups = MaximumPaintBrandCount;

	for (int i = 0; i <= NumPaintGroups; i++)
	{
		sprintf(PaintBrandID, "Group%d", i);

		APaintGroup.BrandNameHash = mINI_ReadHashS(PaintGroupsINI, PaintBrandID, "BrandName", GetDefaultPaintBrandName(i));
		APaintGroup.StringHash = mINI_ReadHashS(PaintGroupsINI, PaintBrandID, "String", GetDefaultPaintBrandString(i));

		PaintGroups_temp.push_back(APaintGroup); // Add to temp list
	}

	PaintGroups = std::move(PaintGroups_temp);
}

