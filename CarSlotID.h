#pragma once

#include "stdafx.h"
#include "stdio.h"

enum CAR_SLOT_ID : int
{
	__INVALID = -1,
	BASE,
	DAMAGE_FRONT_WINDOW,
	DAMAGE_BODY,
	DAMAGE_COP_LIGHTS,
	DAMAGE_COP_SPOILER,
	DAMAGE_FRONT_WHEEL,
	DAMAGE_LEFT_BRAKELIGHT,
	DAMAGE_RIGHT_BRAKELIGHT,
	DAMAGE_LEFT_HEADLIGHT,
	DAMAGE_RIGHT_HEADLIGHT,
	DAMAGE_HOOD,
	DAMAGE_BUSHGUARD,
	DAMAGE_FRONT_BUMPER,
	DAMAGE_RIGHT_DOOR,
	DAMAGE_RIGHT_REAR_DOOR,
	DAMAGE_TRUNK,
	DAMAGE_REAR_BUMPER,
	DAMAGE_REAR_LEFT_WINDOW,
	DAMAGE_FRONT_LEFT_WINDOW,
	DAMAGE_FRONT_RIGHT_WINDOW,
	DAMAGE_REAR_RIGHT_WINDOW,
	DAMAGE_LEFT_DOOR,
	DAMAGE_LEFT_REAR_DOOR,
	BODY,
	FRONT_BRAKE,
	FRONT_LEFT_WINDOW,
	FRONT_RIGHT_WINDOW,
	FRONT_WINDOW,
	INTERIOR,
	LEFT_BRAKELIGHT,
	LEFT_BRAKELIGHT_GLASS,
	LEFT_HEADLIGHT,
	LEFT_HEADLIGHT_GLASS,
	LEFT_SIDE_MIRROR,
	REAR_BRAKE,
	REAR_LEFT_WINDOW,
	REAR_RIGHT_WINDOW,
	REAR_WINDOW,
	RIGHT_BRAKELIGHT,
	RIGHT_BRAKELIGHT_GLASS,
	RIGHT_HEADLIGHT,
	RIGHT_HEADLIGHT_GLASS,
	RIGHT_SIDE_MIRROR,
	DRIVER,
	SPOILER,
	UNIVERSAL_SPOILER_BASE,
	DAMAGE0_FRONT,
	DAMAGE0_FRONTLEFT,
	DAMAGE0_FRONTRIGHT,
	DAMAGE0_REAR,
	DAMAGE0_REARLEFT,
	DAMAGE0_REARRIGHT,
	ATTACHMENT0,
	ATTACHMENT1,
	ATTACHMENT2,
	ATTACHMENT3,
	ATTACHMENT4,
	ATTACHMENT5,
	ATTACHMENT6,
	ATTACHMENT7,
	ATTACHMENT8,
	ATTACHMENT9,
	ROOF,
	HOOD,
	HEADLIGHT,
	BRAKELIGHT,
	FRONT_WHEEL,
	REAR_WHEEL,
	SPINNER,
	LICENSE_PLATE,
	DECAL_FRONT_WINDOW_WIDE_MEDIUM,
	DECAL_REAR_WINDOW_WIDE_MEDIUM,
	DECAL_LEFT_DOOR_RECT_MEDIUM,
	DECAL_RIGHT_DOOR_RECT_MEDIUM,
	DECAL_LEFT_QUARTER_RECT_MEDIUM,
	DECAL_RIGHT_QUARTER_RECT_MEDIUM,
	BASE_PAINT,
	VINYL_LAYER0,
	PAINT_RIM,
	VINYL_COLOUR0_0,
	VINYL_COLOUR0_1,
	VINYL_COLOUR0_2,
	VINYL_COLOUR0_3,
	DECAL_FRONT_WINDOW_TEX0,
	DECAL_FRONT_WINDOW_TEX1,
	DECAL_FRONT_WINDOW_TEX2,
	DECAL_FRONT_WINDOW_TEX3,
	DECAL_FRONT_WINDOW_TEX4,
	DECAL_FRONT_WINDOW_TEX5,
	DECAL_FRONT_WINDOW_TEX6,
	DECAL_FRONT_WINDOW_TEX7,
	DECAL_REAR_WINDOW_TEX0,
	DECAL_REAR_WINDOW_TEX1,
	DECAL_REAR_WINDOW_TEX2,
	DECAL_REAR_WINDOW_TEX3,
	DECAL_REAR_WINDOW_TEX4,
	DECAL_REAR_WINDOW_TEX5,
	DECAL_REAR_WINDOW_TEX6,
	DECAL_REAR_WINDOW_TEX7,
	DECAL_LEFT_DOOR_TEX0,
	DECAL_LEFT_DOOR_TEX1,
	DECAL_LEFT_DOOR_TEX2,
	DECAL_LEFT_DOOR_TEX3,
	DECAL_LEFT_DOOR_TEX4,
	DECAL_LEFT_DOOR_TEX5,
	DECAL_LEFT_DOOR_TEX6,
	DECAL_LEFT_DOOR_TEX7,
	DECAL_RIGHT_DOOR_TEX0,
	DECAL_RIGHT_DOOR_TEX1,
	DECAL_RIGHT_DOOR_TEX2,
	DECAL_RIGHT_DOOR_TEX3,
	DECAL_RIGHT_DOOR_TEX4,
	DECAL_RIGHT_DOOR_TEX5,
	DECAL_RIGHT_DOOR_TEX6,
	DECAL_RIGHT_DOOR_TEX7,
	DECAL_LEFT_QUARTER_TEX0,
	DECAL_LEFT_QUARTER_TEX1,
	DECAL_LEFT_QUARTER_TEX2,
	DECAL_LEFT_QUARTER_TEX3,
	DECAL_LEFT_QUARTER_TEX4,
	DECAL_LEFT_QUARTER_TEX5,
	DECAL_LEFT_QUARTER_TEX6,
	DECAL_LEFT_QUARTER_TEX7,
	DECAL_RIGHT_QUARTER_TEX0,
	DECAL_RIGHT_QUARTER_TEX1,
	DECAL_RIGHT_QUARTER_TEX2,
	DECAL_RIGHT_QUARTER_TEX3,
	DECAL_RIGHT_QUARTER_TEX4,
	DECAL_RIGHT_QUARTER_TEX5,
	DECAL_RIGHT_QUARTER_TEX6,
	DECAL_RIGHT_QUARTER_TEX7,
	WINDOW_TINT,
	CUSTOM_HUD,
	HUD_BACKING_COLOUR,
	HUD_NEEDLE_COLOUR,
	HUD_CHARACTER_COLOUR,
	CV,
	WHEEL_MANUFACTURER,
	MISC,
	__NUM = 139,
	__MODEL_FIRST = 0,
	__MODEL_LAST = 75,
	__MODEL_NUM = 76,
	__FIRST_NONRENDER = 76,
	__LAST_NONRENDER = 138,
	__NONRENDER_NUM = 63,
	__ATTACHMENT_MODEL_FIRST = 52,
	__ATTACHMENT_MODEL_LAST = 61,
	__ATTACHMENT_MODEL_NUM = 10,
	__DAMAGE_MODEL_FIRST = 1,
	__DAMAGE_MODEL_LAST = 22,
	__DAMAGE_MODEL_NUM = 22,
	__DAMAGE_PLAYER_MODEL_FIRST = 46,
	__DAMAGE_PLAYER_MODEL_LAST = 51,
	__DAMAGE_PLAYER_MODEL_NUM = 6,
	__DECAL_MODEL_FIRST = 70,
	__DECAL_MODEL_LAST = 75,
	__DECAL_MODEL_NUM = 6,
};
