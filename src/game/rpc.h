/*
 *    rpc.h    --    header for discord RPC
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 29, 2022
 *
 *    This file is the interface for discord RPC to be used by the game.
 */
#pragma once

#include "libchik.h"

#include "../thirdparty/discord_game_sdk.h"

typedef struct {
    struct IDiscordCore                *apCore;
    struct IDiscordUserManager         *apUsers;
    struct IDiscordAchievementManager  *apAchievements;
    struct IDiscordActivityManager     *apActivities;
    struct IDiscordRelationshipManager *apRelationships;
    struct IDiscordApplicationManager  *apApp;
    struct IDiscordLobbyManager        *apLobbies;
    DiscordUserId                       aUserId;
} discord_t;

/*
 *    Updates the activity.
 *
 *    @param void *                 The application data.
 *    @param enum EDiscordResult    The result of the operation.
 */
void rpc_update_activity_callback(void *spData, enum EDiscordResult sResult);

/*
 *    Returns if the relationship is a friend.
 *
 *    @param void *                          The application data.
 *    @param struct DiscordRelationship *    The relationship.
 *
 *    @return unsigned int                            1 if the relationship is a friend,
 * 0 otherwise.
 */
unsigned int rpc_relationship_pass_filter(void                       *spData,
                                          struct DiscordRelationship *spRelationship);

/*
 *    Returns if the relationship is a friend and the user is less cool than the
 * application.
 *    ... ok copilot...
 *    To be fair, I don't know why this was in the example.
 *
 *    @param void *                          The application data.
 *    @param struct DiscordRelationship *    The relationship.
 *
 *    @return unsigned int                            1 if the relationship is a friend
 * and the user is less cool than the application, 0 otherwise.
 */
unsigned int rpc_relationship_snowflake_filter(
    void *spData, struct DiscordRelationship *spRelationship);

/*
 *    Updates the status.
 *
 *    @param void *                 The application data.
 */
void rpc_update_status(void *spData);

/*
 *    Callback for when relationships refresh.
 *
 *    @param void *                 The application data.
 */
void rpc_relationship_callback(void *spData);

/*
 *    Callback for when the user updates.
 *
 *    @param void *                 The application data.
 */
void rpc_user_callback(void *spData);

/*
 *    Callback for when the client receives authentication.
 *
 *    @param void *                         The application data.
 *    @param enum EDiscordResult            The result of the operation.
 *    @param struct DiscordOAuth2Token *    The OAuth2 data.
 */
void rpc_oauth2_callback(void *spData, enum EDiscordResult sResult,
                         struct DiscordOAuth2Token *spToken);

/*
 *    Callback for when the client receives an invite.
 *
 *    @param void *                   The application data.
 *    @param enum EDiscordResult      The result of the operation.
 *    @param struct DiscordLobby *    The invite data.
 */
void rpc_lobby_callback(void *spData, enum EDiscordResult sResult,
                        struct DiscordLobby *spLobby);

/*
 *    Initializes the discord RPC.
 */
void setup_rpc(void);

/*
 *    Updates discord activity.
 */
void update_rpc(void);