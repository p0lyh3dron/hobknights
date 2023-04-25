/*
 *    rpc.h    --    header for discord RPC
 *
 *    Authored by Karl "p0lyh3dron" Kreuze on April 29, 2022
 *
 *    This file is the interface for discord RPC to be used by the game.
 */
#include "rpc.h"

#include <assert.h>

#define DISCORD_REQUIRE(x) assert(x == DiscordResult_Ok)
/*
 *    Updates the activity.
 *
 *    @param void *                 The pApplication data.
 *    @param enum EDiscordResult    The result of the operation.
 */
void rpc_update_activity_callback(void *spData, enum EDiscordResult sResult) {
    DISCORD_REQUIRE(sResult);
}

/*
 *    Returns if the relationship is a friend.
 *
 *    @param void *                          The pApplication data.
 *    @param struct DiscordRelationship *    The relationship.
 *
 *    @return unsigned int                            1 if the relationship is a friend,
 * 0 otherwise.
 */
unsigned int rpc_relationship_pass_filter(void                       *spData,
                                          struct DiscordRelationship *spRelationship) {
    return (spRelationship->type == DiscordRelationshipType_Friend);
}

/*
 *    Returns if the relationship is a friend and the user is less cool than the
 * pApplication.
 *    ... ok copilot...
 *    To be fair, I don't know why this was in the example.
 *
 *    @param void *                          The pApplication data.
 *    @param struct DiscordRelationship *    The relationship.
 *
 *    @return unsigned int                            1 if the relationship is a friend
 * and the user is less cool than the pApplication, 0 otherwise.
 */
unsigned int rpc_relationship_snowflake_filter(
    void *spData, struct DiscordRelationship *spRelationship) {
    discord_t *pApp = (discord_t *)spData;

    return (spRelationship->type == DiscordRelationshipType_Friend &&
            spRelationship->user.id < pApp->aUserId);
}

/*
 *    Updates the status.
 *
 *    @param void *                 The pApplication data.
 */
void rpc_update_status(void *spData) {
    discord_t *pApp = (discord_t *)spData;

    struct DiscordActivity activity;
    memset(&activity, 0, sizeof(activity));
    sprintf(activity.details, "CPU has crunched %d frames", 0);
    sprintf(activity.state, "FPS: %f", 0.f);

    activity.type             = DiscordActivityType_Playing;
    activity.timestamps.start = 0;

    pApp->apActivities->update_activity(pApp->apActivities, &activity, pApp,
                                        rpc_update_activity_callback);
}

/*
 *    Callback for when relationships refresh.
 *
 *    @param void *                 The application data.
 */
void rpc_relationship_callback(void *spData) { rpc_update_status(spData); }

/*
 *    Callback for when the user updates.
 *
 *    @param void *                 The application data.
 */
void rpc_user_callback(void *spData) {
    discord_t         *pApp = (discord_t *)spData;
    struct DiscordUser user;
    pApp->apUsers->get_current_user(pApp->apUsers, &user);
    pApp->aUserId = user.id;
}

/*
 *    Callback for when the client receives authentication.
 *
 *    @param void *                         The application data.
 *    @param enum EDiscordResult            The result of the operation.
 *    @param struct DiscordOAuth2Token *    The OAuth2 data.
 */
void rpc_oauth2_callback(void *spData, enum EDiscordResult sResult,
                         struct DiscordOAuth2Token *spToken) {
    if (sResult == DiscordResult_Ok) {
        log_note("OAuth2 token: %s\n", spToken->access_token);
    } else {
        log_error("GetOAuth2Token failed with %d\n", (int)sResult);
    }
}

/*
 *    Callback for when the client receives an invite.
 *
 *    @param void *                   The application data.
 *    @param enum EDiscordResult      The result of the operation.
 *    @param struct DiscordLobby *    The invite data.
 */
void rpc_lobby_callback(void *spData, enum EDiscordResult sResult,
                        struct DiscordLobby *spLobby) {
    log_note("LobbyConnect returned %d\n", (int)sResult);
}

discord_t gDiscord;

/*
 *    Initializes the discord RPC.
 */
void setup_rpc(void) {
    memset(&gDiscord, 0, sizeof(gDiscord));

    static struct IDiscordUserEvents uEvents;
    memset(&uEvents, 0, sizeof(uEvents));
    uEvents.on_current_user_update = &rpc_user_callback;

    static struct IDiscordActivityEvents aEvents;
    memset(&aEvents, 0, sizeof(aEvents));

    static struct IDiscordRelationshipEvents rEvents;
    memset(&rEvents, 0, sizeof(rEvents));
    rEvents.on_refresh = &rpc_relationship_callback;

    static struct DiscordCreateParams params;
    DiscordCreateParamsSetDefault(&params);
    params.client_id           = 967274265151950848;
    params.flags               = DiscordCreateFlags_Default;
    params.event_data          = &gDiscord;
    params.activity_events     = &aEvents;
    params.relationship_events = &rEvents;
    params.user_events         = &uEvents;
    DISCORD_REQUIRE(DiscordCreate(DISCORD_VERSION, &params, &gDiscord.apCore));

    gDiscord.apUsers = gDiscord.apCore->get_user_manager(gDiscord.apCore);
    gDiscord.apAchievements =
        gDiscord.apCore->get_achievement_manager(gDiscord.apCore);
    gDiscord.apActivities =
        gDiscord.apCore->get_activity_manager(gDiscord.apCore);
    gDiscord.apApp     = gDiscord.apCore->get_application_manager(gDiscord.apCore);
    gDiscord.apLobbies = gDiscord.apCore->get_lobby_manager(gDiscord.apCore);

    gDiscord.apLobbies->connect_lobby_with_activity_secret(
        gDiscord.apLobbies, "invalid_secret", &gDiscord, &rpc_lobby_callback);

    gDiscord.apApp->get_oauth2_token(gDiscord.apApp, &gDiscord,
                                     &rpc_oauth2_callback);

    DiscordBranch branch;
    gDiscord.apApp->get_current_branch(gDiscord.apApp, &branch);
    log_note("Discord branch: %s\n", branch);

    gDiscord.apRelationships =
        gDiscord.apCore->get_relationship_manager(gDiscord.apCore);
}

void update_rpc(void) {
    DISCORD_REQUIRE(gDiscord.apCore->run_callbacks(gDiscord.apCore));
    rpc_update_status(&gDiscord);
}