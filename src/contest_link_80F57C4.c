#include "global.h"
#include "alloc.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "bg.h"
#include "contest.h"
#include "contest_link_80F57C4.h"
#include "contest_link_80FC4F4.h"
#include "decompress.h"
#include "dma3.h"
#include "event_data.h"
#include "field_specials.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "link.h"
#include "link_rfu.h"
#include "load_save.h"
#include "main.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "random.h"
#include "save.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "trig.h"
#include "tv.h"
#include "util.h"
#include "window.h"
#include "constants/game_stat.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/vars.h"

struct ContestLinkUnk0
{
    u8 unk0;
    u8 unk1;
    u8 taskId;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 spriteId;
    u8 unk9;
    u8 unkA;
    s16 unkC[4];
    u8 unk14;
    u8 filler15[0x3];
};

struct ContestLinkUnk14
{
    int unk0;
    int unk4;
    u32 unk8;
    u32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
};

struct ContestLinkUnk4
{
    struct ContestLinkUnk14 unk0[4];
};

struct ContestLink80F57C4
{
    struct ContestLinkUnk0 *unk0;
    struct ContestLinkUnk4 *unk4;
    u8 *unk8;
    u8 *unkC[4];
    u8 *unk1C;
};

EWRAM_DATA struct ContestLink80F57C4 *gUnknown_0203A034 = NULL;

extern const struct CompressedSpriteSheet gMonFrontPicTable[];
extern const struct BgTemplate gUnknown_0858D888[4];
extern const struct WindowTemplate gUnknown_0858D898[];
extern const struct CompressedSpriteSheet gUnknown_0858D878[];
extern const struct CompressedSpritePalette gUnknown_0858D880[];
extern const struct SpriteSheet gUnknown_0858D8E0;
extern const struct SpriteTemplate gSpriteTemplate_858D8C8;
extern const u8 gUnknown_0858D8E8[];
extern const u8 gUnknown_0858D6D0[];
extern const struct SpriteTemplate gSpriteTemplate_858D7F8;
extern const struct SpriteSheet gUnknown_0858D810[];
extern const struct SpritePalette gUnknown_0858D850;
extern const struct SpriteTemplate gSpriteTemplate_858D860;

extern void sub_81D9DE4(u8);

static void sub_80F6A9C(void);
static void sub_80F71C8(void);
u8 sub_80F7310(u8, u8);
s8 sub_80F7364(u8, u8);
static void sub_80F7ED0(int, u8 *, int);
static void sub_80F7DF4(void);
static void LoadAllContestMonIcons(u8, u8);
static void sub_80F6DC0(void);
static void sub_80F6AE8(void);
static void sub_80F5CE4(u8);
static void sub_80F5C00(void);
static void sub_80F68B4(u8);
static void sub_80F7880(void);
static void sub_80F5C24(void);
static void sub_80F707C(const u8 *);
static void sub_80F5ED8(u8);
static void sub_80F5F14(u8);
static void sub_80F5F30(u8);
static void sub_80F5F74(u8);
static void sub_80F7144(void);
static void sub_80F68F0(u8);
s16 sub_80F6B78(const u8 *, u8);
static void sub_80F6E9C(s16, u16, u16, u16);
static void sub_80F6058(u8);
static void sub_80F7A80(u8, u8);
void sub_80F7CA8(u8);
static void sub_80F6EF4(u16);
static void sub_80F60F0(u8);
static void sub_80F616C(u8);
static void sub_80F6204(u8);
static void sub_80F73DC(u8);
static void sub_80F74BC(u8);
static void sub_80F753C(u8);
static void sub_80F77E0(u8, u8);
static void sub_80F7824(u8);
static void sub_80F6404(u8);
static void sub_80F75A8(struct Sprite *);
static void sub_80F7670(u8);
static void sub_80F7620(struct Sprite *);
static void sub_80F66B4(u8);
static void sub_80F671C(u8);
static void sub_80F677C(u8);
static void sub_80F67C4(u8);
static void sub_80F6820(u8);
static void sub_80F7E64(void);
static void sub_80F6F68(struct Sprite *);
static void sub_80F7014(struct Sprite *);
static void sub_80F6FDC(struct Sprite *);
static void sub_80F8508(u8);
static void sub_80F8568(u8);
static void sub_80F8584(u8);
static void sub_80F85A0(u8);
static void sub_80F85BC(u8);
static void sub_80F86B8(u8);
static void sub_80F878C(u8);
static void sub_80F87B4(u8);

void sub_80F57C4(void)
{
    int i;

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, gUnknown_0858D888, ARRAY_COUNT(gUnknown_0858D888));
    for (i = 0; i < 4; i++)
        SetBgTilemapBuffer(i, gUnknown_0203A034->unkC[i]);

    InitWindows(gUnknown_0858D898);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_MOSAIC, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG1 | WINOUT_WIN01_BG2 | WINOUT_WIN01_BG3 | WINOUT_WIN01_CLR | WINOUT_WINOBJ_BG_ALL | WINOUT_WINOBJ_OBJ | WINOUT_WINOBJ_CLR);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WIN1H, 0);
    SetGpuReg(REG_OFFSET_WIN1V, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON | DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJWIN_ON);
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    gBattle_BG1_X = 0;
    gBattle_BG1_Y = 0;
    gBattle_BG2_X = 0;
    gBattle_BG2_Y = 0;
    gBattle_BG3_X = 0;
    gBattle_BG3_Y = 0;
    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    gBattle_WIN1H = 0;
    gBattle_WIN1V = 0;
}

void sub_80F591C(void)
{
    int i, j;
    s8 var0;
    s8 var1;
    int var2;
    u16 tile1, tile2;

    LZDecompressVram(gUnknown_08C19588, (void *)BG_CHAR_ADDR(0));
    CopyToBgTilemapBuffer(3, gUnknown_08C1A12C, 0, 0);
    CopyToBgTilemapBuffer(2, gUnknown_08C1A000, 0, 0);
    CopyToBgTilemapBuffer(0, gUnknown_08C19EEC, 0, 0);
    sub_80F71C8();
    LoadCompressedPalette(gUnknown_08C1A2B4, 0, 0x200);
    LoadPalette(gUnknown_0858D6B0, 0xF0, 0x20);

    for (i = 0; i < 4; i++)
    {
        var0 = sub_80F7310(i, 1);
        var1 = sub_80F7364(i, 1);
        for (j = 0; j < 10; j++)
        {
            tile1 = 0x60B2;
            if (j < var0)
                tile1 += 2;

            var2 = var1;
            if (var1 < 0)
                var2 = -var2;

            if (j < var2)
            {
                tile2 = 0x60A4;
                if (var1 < 0)
                    tile2 += 2;
            }
            else
            {
                tile2 = 0x60A2;
            }

            FillBgTilemapBufferRect_Palette0(1, tile1, j + 19, i * 3 + 5, 1, 1);
            FillBgTilemapBufferRect_Palette0(1, tile2, j + 19, i * 3 + 6, 1, 1);
        }
    }

    CopyBgTilemapBufferToVram(0);
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(3);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void sub_80F5A74(u8 monIndex)
{
    struct ContestPokemon *mon = &gContestMons[monIndex];
    u8 *str = gDisplayedStringBattle;
    if (monIndex == gContestPlayerMonIndex)
        str = StringCopy(gDisplayedStringBattle, gText_ColorDarkGrey);

    StringCopy(str, mon->nickname);
    sub_80F7ED0(monIndex, gDisplayedStringBattle, 0);
    StringCopy(str, gText_Slash);
    StringAppend(str, mon->trainerName);
    sub_80F7ED0(monIndex, gDisplayedStringBattle, 50);
}

void sub_80F5AE0(void)
{
    int i;

    for (i = 0; i < 4; i++)
        sub_80F5A74(i);

    CopyBgTilemapBufferToVram(1);
}

void sub_80F5B00(void)
{
    gPaletteFade.bufferTransferDisabled = 1;
    SetVBlankCallback(NULL);
    sub_80F7DF4();
    sub_80F57C4();
    ScanlineEffect_Clear();
    ResetPaletteFade();
    ResetSpriteData();
    ResetTasks();
    FreeAllSpritePalettes();
    sub_80F591C();
    sub_80F6A9C();
    LoadAllContestMonIcons(0, 1);
    sub_80F5AE0();
    memset(gUnknown_0203A034->unk0, 0, sizeof(*gUnknown_0203A034->unk0));
    memset(gUnknown_0203A034->unk4, 0, sizeof(*gUnknown_0203A034->unk4));
    sub_80F6DC0();
    sub_80F6AE8();
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
    gPaletteFade.bufferTransferDisabled = 0;
    gUnknown_0203A034->unk0->taskId = CreateTask(sub_80F5CE4, 5);
    SetMainCallback2(sub_80F5C00);
    gBattle_WIN1H = 0x00F0;
    gBattle_WIN1V = 0x80A0;
    CreateTask(sub_80F68B4, 20);
    sub_80F7880();
    if (gIsLinkContest & 0x2)
        gPaletteFade.bufferTransferDisabled = 1;
    else
        PlayBGM(MUS_CON_K);

    SetVBlankCallback(sub_80F5C24);
}

static void sub_80F5C00(void)
{
    AnimateSprites();
    BuildOamBuffer();
    RunTasks();
    UpdatePaletteFade();
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(2);
}

static void sub_80F5C24(void)
{
    SetGpuReg(REG_OFFSET_BG0HOFS, gBattle_BG0_X);
    SetGpuReg(REG_OFFSET_BG0VOFS, gBattle_BG0_Y);
    SetGpuReg(REG_OFFSET_BG1HOFS, gBattle_BG1_X);
    SetGpuReg(REG_OFFSET_BG1VOFS, gBattle_BG1_Y);
    SetGpuReg(REG_OFFSET_BG2HOFS, gBattle_BG2_X);
    SetGpuReg(REG_OFFSET_BG2VOFS, gBattle_BG2_Y);
    SetGpuReg(REG_OFFSET_BG3HOFS, gBattle_BG3_X);
    SetGpuReg(REG_OFFSET_BG3VOFS, gBattle_BG3_Y);
    SetGpuReg(REG_OFFSET_WIN0H, gBattle_WIN0H);
    SetGpuReg(REG_OFFSET_WIN0V, gBattle_WIN0V);
    SetGpuReg(REG_OFFSET_WIN1H, gBattle_WIN1H);
    SetGpuReg(REG_OFFSET_WIN1V, gBattle_WIN1V);
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
    ScanlineEffect_InitHBlankDmaTransfer();
}

static void sub_80F5CE4(u8 taskId)
{
    u16 var;

    if (gIsLinkContest & 1)
    {
        switch (gTasks[taskId].data[0])
        {
        case 0:
            sub_80DBED4();
            if (gContestFinalStandings[gContestPlayerMonIndex] == 0)
            {
                IncrementGameStat(GAME_STAT_WON_LINK_CONTEST);
                gSpecialVar_0x8005 = 8;
                InterviewBefore();
                if (gSpecialVar_Result != 1)
                    InterviewAfter();
            }

            sub_813BADC(2);
            sub_80DEDA8(gSpecialVar_ContestRank);
            sub_80DEDA8(0xFE);
            gUnknown_02039F5C = 1;
            gUnknown_02039F5D = sub_80DEFA8(0xFE, 0);
            var = VarGet(VAR_0x4086);
            VarSet(VAR_0x4086, 0);
            SetContinueGameWarpStatusToDynamicWarp();
            TrySavingData(SAVE_LINK);
            ClearContinueGameWarpStatus2();
            VarSet(VAR_0x4086, var);
            gTasks[taskId].data[0]++;
            break;
        case 1:
            gTasks[taskId].data[0]++;
            if (!(gIsLinkContest & 0x2))
                gTasks[taskId].data[0] = 100;
            break;
        case 2:
            if (IsLinkTaskFinished())
            {
                sub_800ADF8();
                gTasks[taskId].data[0]++;
            }
            return;
        case 3:
            if (IsLinkTaskFinished() == TRUE)
            {
                PlayBGM(MUS_CON_K);
                gPaletteFade.bufferTransferDisabled = 0;
                gTasks[taskId].data[0]++;
                break;
            }
            return;
        }
    }

    if (!gPaletteFade.active)
    {
        gTasks[taskId].data[0] = 0;
        if (gIsLinkContest & 0x1)
        {
            sub_80F707C(gText_CommunicationStandby);
            gTasks[taskId].func = sub_80F5ED8;
        }
        else
        {
            IncrementGameStat(GAME_STAT_ENTERED_CONTEST);
            if (gContestFinalStandings[gContestPlayerMonIndex] == 0)
                IncrementGameStat(GAME_STAT_WON_CONTEST);

            sub_80DEDA8(gSpecialVar_ContestRank);
            sub_80DEDA8(0xFE);
            gUnknown_02039F5C = 1;
            gUnknown_02039F5D = sub_80DEFA8(0xFE, 0);
            sub_813BADC(2);
            gTasks[taskId].func = sub_80F5F74;
        }
    }
}

static void sub_80F5ED8(u8 taskId)
{
    if (gReceivedRemoteLinkPlayers)
    {
        CreateTask(sub_80F5F14, 0);
        gTasks[taskId].func = TaskDummy;
    }
}

static void sub_80F5F14(u8 taskId)
{
    SetTaskFuncWithFollowupFunc(taskId, sub_80FC998, sub_80F5F30);
}

static void sub_80F5F30(u8 taskId)
{
    if (IsLinkTaskFinished())
    {
        DestroyTask(taskId);
        gTasks[gUnknown_0203A034->unk0->taskId].func = sub_80F5F74;
        sub_80F7144();
    }
}

static void sub_80F5F74(u8 taskId)
{
    s16 var0;

    if (gTasks[taskId].data[0] == 0)
    {
        CreateTask(sub_80F68F0, 20);
        var0 = sub_80F6B78(gText_AnnouncingResults, gUnknown_0203A034->unk0->unk0);
        sub_80F6E9C(var0, 144, 120, 1088);
        gTasks[taskId].data[0]++;
    }
    else if (gTasks[taskId].data[0] == 1)
    {
        if (gUnknown_0203A034->unk0->unk4 == 0)
        {
            gTasks[taskId].data[1] = 0;
            gTasks[taskId].data[0]++;
        }
    }
    else if (gTasks[taskId].data[0] == 2)
    {
        if (++gTasks[taskId].data[1] == 21)
        {
            gTasks[taskId].data[1] = 0;
            gTasks[taskId].data[0]++;
        }
    }
    else if (gTasks[taskId].data[0] == 3)
    {
        var0 = sub_80F6B78(gText_PreliminaryResults, gUnknown_0203A034->unk0->unk0);
        sub_80F6E9C(var0, 144, -1, 1088);
        gTasks[taskId].data[0]++;
    }
    else if (gTasks[taskId].data[0] == 4)
    {
        if (gUnknown_0203A034->unk0->unk4 == 2)
        {
            gTasks[taskId].data[0] = 0;
            gTasks[taskId].func = sub_80F6058;
        }
    }
}

static void sub_80F6058(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (!gUnknown_0203A034->unk0->unkA)
        {
            sub_80F7A80(0, gTasks[taskId].data[2]++);
            if (!gUnknown_0203A034->unk0->unk14)
                gTasks[taskId].data[0] = 2;
            else
                gTasks[taskId].data[0]++;
        }
        break;
    case 1:
        if (!gUnknown_0203A034->unk0->unk14)
            gTasks[taskId].data[0] = 0;
        break;
    case 2:
        sub_80F6EF4(1088);
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].func = sub_80F60F0;
        break;
    }
}

static void sub_80F60F0(u8 taskId)
{
    s16 var0;

    if (gUnknown_0203A034->unk0->unk4 == 0)
    {
        if (++gTasks[taskId].data[1] == 21)
        {
            gTasks[taskId].data[1] = 0;
            var0 = sub_80F6B78(gText_Round2Results, gUnknown_0203A034->unk0->unk0);
            sub_80F6E9C(var0, 144, -1, 1088);
        }
    }
    else if (gUnknown_0203A034->unk0->unk4 == 2)
    {
        gTasks[taskId].func = sub_80F616C;
    }
}

static void sub_80F616C(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (!gUnknown_0203A034->unk0->unkA)
        {
            sub_80F7A80(1, gTasks[taskId].data[2]++);
            if (!gUnknown_0203A034->unk0->unk14)
                gTasks[taskId].data[0] = 2;
            else
                gTasks[taskId].data[0]++;
        }
        break;
    case 1:
        if (!gUnknown_0203A034->unk0->unk14)
            gTasks[taskId].data[0] = 0;
        break;
    case 2:
        sub_80F6EF4(1088);
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].func = sub_80F6204;
        break;
    }
}

static void sub_80F6204(u8 taskId)
{
    int i;
    u8 newTaskId;
    u8 buffer[100];
    s16 var0;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        if (!gUnknown_0203A034->unk0->unk4)
            gTasks[taskId].data[0]++;
        break;
    case 1:
        if (++gTasks[taskId].data[1] == 31)
        {
            gTasks[taskId].data[1] = 0;
            gTasks[taskId].data[0]++;
        }
        break;
    case 2:
        for (i = 0; i < 4; i++)
        {
            newTaskId = CreateTask(sub_80F73DC, 10);
            gTasks[newTaskId].data[0] = gContestFinalStandings[i];
            gTasks[newTaskId].data[1] = i;
        }
        gTasks[taskId].data[0]++;
        break;
    case 3:
        if (gUnknown_0203A034->unk0->unk5 == 4)
        {
            if (++gTasks[taskId].data[1] == 31)
            {
                gTasks[taskId].data[1] = 0;
                CreateTask(sub_80F74BC, 10);
                gTasks[taskId].data[0]++;
                for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
                    ;

                sub_80F77E0(i, 14);
            }
        }
        break;
    case 4:
        if (++gTasks[taskId].data[1] == 21)
        {
            gTasks[taskId].data[1] = 0;
            for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
                ;

            StringCopy(gStringVar1, gContestMons[i].trainerName);
            sub_81DB5AC(gStringVar1);
            StringCopy(gStringVar2, gContestMons[i].nickname);
            StringExpandPlaceholders(buffer, gText_Var1sVar2Won);
            var0 = sub_80F6B78(buffer, gUnknown_0203A034->unk0->unk0);
            sub_80F6E9C(var0, 144, -1, 1088);
            gTasks[taskId].data[0]++;
        }
        break;
    case 5:
        gTasks[taskId].data[0] = 0;
        gTasks[taskId].func = sub_80F6404;
        break;
    }
}

static void sub_80F6404(u8 taskId)
{
    int i;
    u8 spriteId;
    u16 species;
    u32 otId;
    u32 personality;
    const struct CompressedSpritePalette *pokePal;

    switch (gTasks[taskId].data[0])
    {
    case 0:
        gBattle_WIN0H = 0x00F0;
        gBattle_WIN0V = 0x5050;
        for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
            ;

        species = gContestMons[i].species;
        personality = gContestMons[i].personality;
        otId = gContestMons[i].otId;
        if (i == gContestPlayerMonIndex)
        {
            HandleLoadSpecialPokePic_2(
                &gMonFrontPicTable[species],
                gMonSpritesGfxPtr->sprites[1],
                species,
                personality);
        }
        else
        {
            HandleLoadSpecialPokePic_DontHandleDeoxys(
                &gMonFrontPicTable[species],
                gMonSpritesGfxPtr->sprites[1],
                species,
                personality);
        }

        pokePal = GetMonSpritePalStructFromOtIdPersonality(species, otId, personality);
        LoadCompressedSpritePalette(pokePal);
        SetMultiuseSpriteTemplateToPokemon(species, B_POSITION_OPPONENT_LEFT);
        gMultiuseSpriteTemplate.paletteTag = pokePal->tag;
        spriteId = CreateSprite(&gMultiuseSpriteTemplate, 272, 80, 10);
        gSprites[spriteId].data[1] = species;
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].callback = sub_80F75A8;
        gUnknown_0203A034->unk0->spriteId = spriteId;
        LoadCompressedSpriteSheet(gUnknown_0858D878);
        LoadCompressedSpritePalette(gUnknown_0858D880);
        CreateTask(sub_80F7670, 10);
        gTasks[taskId].data[0]++;
        break;
    case 1:
        if (++gTasks[taskId].data[3] == 1)
        {
            u8 counter;
            gTasks[taskId].data[3] = 0;
            gTasks[taskId].data[2] += 2;
            if (gTasks[taskId].data[2] > 32)
                gTasks[taskId].data[2] = 32;

            counter = gTasks[taskId].data[2];
            gBattle_WIN0V = ((80 - counter) << 8) | (80 + counter);
            if (counter == 32)
                gTasks[taskId].data[0]++;
        }
        break;
    case 2:
        if (gUnknown_0203A034->unk0->unk6 == 1)
            gTasks[taskId].data[0]++;
        break;
    case 3:
        if (++gTasks[taskId].data[1] == 121)
        {
            gTasks[taskId].data[1] = 0;
            gSprites[gUnknown_0203A034->unk0->spriteId].callback = sub_80F7620;
            gTasks[taskId].data[0]++;
        }
        break;
    case 4:
        if (gUnknown_0203A034->unk0->unk6 == 2)
        {
            u8 top = (gBattle_WIN0V >> 8);
            top += 2;
            if (top > 80)
                top = 80;

            gBattle_WIN0V = (top << 8) | (160 - top);;
            if (top == 80)
                gTasks[taskId].data[0]++;
        }
        break;
    case 5:
        if (gUnknown_0203A034->unk0->unk6 == 2)
        {
            gUnknown_0203A034->unk0->unk9 = 1;
            gTasks[taskId].data[0] = 0;
            gTasks[taskId].func = sub_80F66B4;
        }
        break;
    }
}

static void sub_80F66B4(u8 taskId)
{
    int i;
    u16 nationalDexNum;

    if (gMain.newKeys & A_BUTTON)
    {
        if (!(gIsLinkContest & 0x1))
        {
            for (i = 0; i < 4; i++)
            {
                nationalDexNum = SpeciesToNationalPokedexNum(gContestMons[i].species);
                GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
            }
        }

        gTasks[taskId].data[10] = 0;
        gTasks[taskId].func = sub_80F671C;
    }
}

static void sub_80F671C(u8 taskId)
{
    if (gIsLinkContest & 0x1)
    {
        if (!gTasks[taskId].data[10])
        {
            sub_80F707C(gText_CommunicationStandby);
            sub_800AC34();
            gTasks[taskId].func = sub_80F677C;
        }
    }
    else
    {
        gTasks[taskId].func = sub_80F67C4;
    }
}

static void sub_80F677C(u8 taskId)
{
    if (!gReceivedRemoteLinkPlayers)
    {
        if (gIsLinkContest & 0x2)
            sub_800E084();

        sub_80F7144();
        gTasks[taskId].func = sub_80F67C4;
    }
}

static void sub_80F67C4(u8 taskId)
{
    if (!(gIsLinkContest & 0x1))
        BravoTrainerPokemonProfile_BeforeInterview2(gContestFinalStandings[gContestPlayerMonIndex]);

    BeginHardwarePaletteFade(0xFF, 0, 0, 16, 0);
    gTasks[taskId].func = sub_80F6820;
}

static void sub_80F6820(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        if (gTasks[taskId].data[1] == 0)
        {
            DestroyTask(gUnknown_0203A034->unk0->unk3);
            BlendPalettes(0x0000FFFF, 16, RGB_BLACK);
            gTasks[taskId].data[1]++;
        }
        else if (gTasks[taskId].data[1] == 1)
        {
            BlendPalettes(0xFFFF0000, 16, RGB_BLACK);
            gTasks[taskId].data[1]++;
        }
        else
        {
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            DestroyTask(taskId);
            FreeAllWindowBuffers();
            SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
            sub_80F7E64();
        }
    }
}

static void sub_80F68B4(u8 taskId)
{
    gBattle_BG3_X += 2;
    gBattle_BG3_Y += 1;
    if (gBattle_BG3_X > 255)
        gBattle_BG3_X -= 255;
    if (gBattle_BG3_Y > 255)
        gBattle_BG3_Y -= 255;
}

static void sub_80F68F0(u8 taskId)
{
    if (++gTasks[taskId].data[0] == 2)
    {
        gTasks[taskId].data[0] = 0;
        if (gTasks[taskId].data[2] == 0)
            gTasks[taskId].data[1]++;
        else
            gTasks[taskId].data[1]--;

        if (gTasks[taskId].data[1] == 16)
            gTasks[taskId].data[2] = 1;
        else if (gTasks[taskId].data[1] == 0)
            gTasks[taskId].data[2] = 0;

        BlendPalette(0x6B, 1, gTasks[taskId].data[1], RGB(30, 22, 11));
        BlendPalette(0x68, 1, gTasks[taskId].data[1], RGB_WHITE);
        BlendPalette(0x6E, 1, gTasks[taskId].data[1], RGB(30, 29, 29));
    }

    if (gTasks[taskId].data[1] == 0)
        gUnknown_0203A034->unk0->unkA = 0;
    else
        gUnknown_0203A034->unk0->unkA = 1;
}

void sub_80F69B8(u16 species, u8 monIndex, u8 srcOffset, u8 useDmaNow, u32 personality)
{
    u8 frameNum;
    const u8 *iconPtr;
    u16 var0;
    u16 var1;

    u8 *contestPlayerMonIndex = &gContestPlayerMonIndex; // fake match
    frameNum = (monIndex == *contestPlayerMonIndex) ? 1 : 0;

    iconPtr = GetMonIconPtr(species, personality, frameNum);
    iconPtr += srcOffset * 0x200 + 0x80;
    if (useDmaNow)
    {
        RequestDma3Copy(iconPtr, (void *)BG_CHAR_ADDR(1) + monIndex * 0x200, 0x180, 1);
        var0 = ((monIndex + 10) << 12);
        var1 = (monIndex * 0x10 + 0x200);
        WriteSequenceToBgTilemapBuffer(1, var1 | var0, 3, monIndex * 3 + 4, 4, 3, 17, 1);
    }
    else
    {
        RequestDma3Copy(iconPtr, (void *)BG_CHAR_ADDR(1) + monIndex * 0x200, 0x180, 1);
    }
}

static void LoadAllContestMonIcons(u8 srcOffset, u8 useDmaNow)
{
    int i;

    for (i = 0; i < 4; i++)
        sub_80F69B8(gContestMons[i].species, i, srcOffset, useDmaNow, gContestMons[i].personality);
}

static void sub_80F6A9C(void)
{
    int i;
    register u16 species asm("r0");

    for (i = 0; i < 4; i++)
    {
        species = GetIconSpecies(gContestMons[i].species, 0);
        LoadPalette(gMonIconPalettes[gMonIconPaletteIndices[species]], i * 0x10 + 0xA0, 0x20);
    }
}

static void sub_80F6AE8(void)
{
    u16 sheet;
    u8 spriteId;

    if (gIsLinkContest & 0x2)
    {
        sub_800E0E8();
        CreateWirelessStatusIndicatorSprite(8, 8);
        gSprites[gWirelessStatusIndicatorSpriteId].subpriority = 1;
        sheet = LoadSpriteSheet(&gUnknown_0858D8E0);
        RequestDma3Fill(0xFFFFFFFF, (void *)BG_CHAR_ADDR(4) + sheet * 0x20, 0x80, 1);
        spriteId = CreateSprite(&gSpriteTemplate_858D8C8, 8, 8, 0);
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
    }
}

// s16 sub_80F6B78(const u8 *text, u8 spriteId)
// {
//     int i;
//     int origWidth, strWidth;
//     const u8 *r8;
//     u8 sp10[0x10];
//     struct WindowTemplate windowTemplate;
//     int spC;
//     u8 *windowTileData;
//     u8 windowId;

//     memset(windowTemplate, 0, sizeof(*windowTemplate));
//     windowTemplate.width = 30;
//     windowTemplate.height = 2;
//     windowId = AddWindow(&windowTemplate);
//     FillWindowPixelBuffer(windowId, 0x11);
//     origWidth = GetStringWidth(1, text, 0) + 9;
//     strWidth = origWidth;
//     if (strWidth < 0)
//         strWidth += 7;

//     strWidth >>= 3;
//     if (strWidth > 30)
//         strWidth = 30;

//     AddTextPrinterParameterized3(windowId, 1, (strWidth * 8 - origWidth) / 2, 1, gUnknown_0858D8E8, -1, text);
//     windowTileData = (u8 *)GetWindowAttribute(windowId, WINDOW_TILE_DATA);
//     r8 = gUnknown_0858D6D0;
//     // ....
// }

NAKED
s16 sub_80F6B78(const u8 *text, u8 spriteId)
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0x44\n\
    adds r5, r0, 0\n\
    lsls r1, 24\n\
    lsrs r7, r1, 24\n\
    add r4, sp, 0x20\n\
    adds r0, r4, 0\n\
    movs r1, 0\n\
    movs r2, 0x8\n\
    bl memset\n\
    movs r0, 0x1E\n\
    strb r0, [r4, 0x3]\n\
    movs r0, 0x2\n\
    strb r0, [r4, 0x4]\n\
    adds r0, r4, 0\n\
    bl AddWindow\n\
    lsls r6, r0, 24\n\
    lsrs r4, r6, 24\n\
    adds r0, r4, 0\n\
    movs r1, 0x11\n\
    bl FillWindowPixelBuffer\n\
    movs r0, 0x1\n\
    adds r1, r5, 0\n\
    movs r2, 0\n\
    bl GetStringWidth\n\
    adds r2, r0, 0\n\
    adds r2, 0x9\n\
    cmp r2, 0\n\
    bge _080F6BC4\n\
    adds r2, 0x7\n\
_080F6BC4:\n\
    asrs r2, 3\n\
    mov r10, r2\n\
    cmp r2, 0x1E\n\
    ble _080F6BD0\n\
    movs r1, 0x1E\n\
    mov r10, r1\n\
_080F6BD0:\n\
    mov r1, r10\n\
    lsls r2, r1, 3\n\
    subs r2, r0\n\
    lsrs r0, r2, 31\n\
    adds r2, r0\n\
    asrs r2, 1\n\
    lsls r2, 24\n\
    lsrs r2, 24\n\
    ldr r0, =gUnknown_0858D8E8\n\
    str r0, [sp]\n\
    movs r0, 0x1\n\
    negs r0, r0\n\
    str r0, [sp, 0x4]\n\
    str r5, [sp, 0x8]\n\
    adds r0, r4, 0\n\
    movs r1, 0x1\n\
    movs r3, 0x1\n\
    bl AddTextPrinterParameterized3\n\
    adds r0, r4, 0\n\
    movs r1, 0x7\n\
    bl GetWindowAttribute\n\
    mov r9, r0\n\
    ldr r2, =gUnknown_0858D6D0\n\
    mov r8, r2\n\
    lsls r1, r7, 4\n\
    adds r1, r7\n\
    lsls r1, 2\n\
    ldr r3, =gSprites\n\
    adds r1, r3\n\
    ldrh r0, [r1, 0x4]\n\
    lsls r0, 22\n\
    lsrs r0, 17\n\
    ldr r2, =0x06010000\n\
    adds r0, r2\n\
    str r0, [sp, 0xC]\n\
    str r6, [sp, 0x38]\n\
    mov r7, sp\n\
    adds r7, 0x1C\n\
    str r7, [sp, 0x2C]\n\
    mov r0, r10\n\
    adds r0, 0x2\n\
    str r0, [sp, 0x30]\n\
    movs r5, 0\n\
    add r7, sp, 0x10\n\
    mov r12, r7\n\
    adds r6, r1, 0\n\
    adds r6, 0x2E\n\
    movs r4, 0x2\n\
_080F6C34:\n\
    adds r0, r6, r5\n\
    movs r7, 0\n\
    ldrsh r1, [r0, r7]\n\
    lsls r0, r1, 4\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    adds r0, r3\n\
    ldrh r0, [r0, 0x4]\n\
    lsls r0, 22\n\
    lsrs r0, 17\n\
    adds r0, r2\n\
    mov r1, r12\n\
    adds r1, 0x4\n\
    mov r12, r1\n\
    subs r1, 0x4\n\
    stm r1!, {r0}\n\
    adds r5, 0x2\n\
    subs r4, 0x1\n\
    cmp r4, 0\n\
    bge _080F6C34\n\
    mov r7, r8\n\
    adds r7, 0x80\n\
    mov r2, r8\n\
    adds r2, 0x40\n\
    str r2, [sp, 0x28]\n\
    mov r0, r8\n\
    adds r0, 0x20\n\
    str r0, [sp, 0x3C]\n\
    mov r1, r8\n\
    adds r1, 0xA0\n\
    str r1, [sp, 0x40]\n\
    adds r2, 0x20\n\
    str r2, [sp, 0x34]\n\
    add r5, sp, 0xC\n\
    movs r6, 0\n\
    movs r4, 0x3\n\
_080F6C7C:\n\
    str r6, [sp, 0x1C]\n\
    ldm r5!, {r1}\n\
    ldr r0, [sp, 0x2C]\n\
    ldr r2, =0x05000100\n\
    bl CpuSet\n\
    subs r4, 0x1\n\
    cmp r4, 0\n\
    bge _080F6C7C\n\
    ldr r5, [sp, 0xC]\n\
    ldr r6, =0x04000008\n\
    mov r0, r8\n\
    adds r1, r5, 0\n\
    adds r2, r6, 0\n\
    bl CpuSet\n\
    movs r0, 0x80\n\
    lsls r0, 1\n\
    adds r1, r5, r0\n\
    adds r0, r7, 0\n\
    adds r2, r6, 0\n\
    bl CpuSet\n\
    movs r2, 0x80\n\
    lsls r2, 2\n\
    adds r1, r5, r2\n\
    adds r0, r7, 0\n\
    adds r2, r6, 0\n\
    bl CpuSet\n\
    movs r7, 0xC0\n\
    lsls r7, 2\n\
    adds r1, r5, r7\n\
    ldr r0, [sp, 0x28]\n\
    adds r2, r6, 0\n\
    bl CpuSet\n\
    movs r4, 0\n\
    cmp r4, r10\n\
    bge _080F6D32\n\
    adds r7, r6, 0\n\
_080F6CCE:\n\
    adds r6, r4, 0x1\n\
    adds r0, r6, 0\n\
    cmp r6, 0\n\
    bge _080F6CDA\n\
    adds r0, r4, 0\n\
    adds r0, 0x8\n\
_080F6CDA:\n\
    asrs r0, 3\n\
    lsls r1, r0, 2\n\
    add r1, sp\n\
    adds r1, 0xC\n\
    lsls r0, 3\n\
    subs r0, r6, r0\n\
    lsls r0, 5\n\
    ldr r1, [r1]\n\
    adds r5, r1, r0\n\
    mov r0, r8\n\
    adds r0, 0xC0\n\
    adds r1, r5, 0\n\
    adds r2, r7, 0\n\
    bl CpuSet\n\
    movs r0, 0x80\n\
    lsls r0, 1\n\
    adds r1, r5, r0\n\
    mov r0, r9\n\
    adds r2, r7, 0\n\
    bl CpuSet\n\
    movs r0, 0xF0\n\
    lsls r0, 2\n\
    add r0, r9\n\
    movs r2, 0x80\n\
    lsls r2, 2\n\
    adds r1, r5, r2\n\
    adds r2, r7, 0\n\
    bl CpuSet\n\
    movs r0, 0xC0\n\
    lsls r0, 2\n\
    adds r1, r5, r0\n\
    mov r0, r8\n\
    adds r0, 0xE0\n\
    adds r2, r7, 0\n\
    bl CpuSet\n\
    movs r1, 0x20\n\
    add r9, r1\n\
    adds r4, r6, 0\n\
    cmp r4, r10\n\
    blt _080F6CCE\n\
_080F6D32:\n\
    adds r2, r4, 0x1\n\
    adds r0, r2, 0\n\
    cmp r2, 0\n\
    bge _080F6D3E\n\
    adds r0, r4, 0\n\
    adds r0, 0x8\n\
_080F6D3E:\n\
    asrs r0, 3\n\
    lsls r1, r0, 2\n\
    add r1, sp\n\
    adds r1, 0xC\n\
    lsls r0, 3\n\
    subs r0, r2, r0\n\
    lsls r0, 5\n\
    ldr r1, [r1]\n\
    adds r5, r1, r0\n\
    ldr r4, =0x04000008\n\
    ldr r0, [sp, 0x3C]\n\
    adds r1, r5, 0\n\
    adds r2, r4, 0\n\
    bl CpuSet\n\
    movs r2, 0x80\n\
    lsls r2, 1\n\
    adds r1, r5, r2\n\
    ldr r0, [sp, 0x40]\n\
    adds r2, r4, 0\n\
    bl CpuSet\n\
    movs r7, 0x80\n\
    lsls r7, 2\n\
    adds r1, r5, r7\n\
    ldr r0, [sp, 0x40]\n\
    adds r2, r4, 0\n\
    bl CpuSet\n\
    movs r0, 0xC0\n\
    lsls r0, 2\n\
    adds r1, r5, r0\n\
    ldr r0, [sp, 0x34]\n\
    adds r2, r4, 0\n\
    bl CpuSet\n\
    ldr r1, [sp, 0x38]\n\
    lsrs r0, r1, 24\n\
    bl RemoveWindow\n\
    ldr r2, [sp, 0x30]\n\
    lsls r1, r2, 3\n\
    movs r0, 0xF0\n\
    subs r0, r1\n\
    asrs r0, 1\n\
    add sp, 0x44\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r1}\n\
    bx r1\n\
    .pool");
}

static void sub_80F6DC0(void)
{
    int i;
    struct SpriteTemplate template;
    u8 spriteIds[8];

    template = gSpriteTemplate_858D7F8;
    for (i = 0; i < 8; i++)
        LoadSpriteSheet(&gUnknown_0858D810[i]);

    LoadSpritePalette(&gUnknown_0858D850);
    for (i = 0; i < 8; i++)
    {
        spriteIds[i] = CreateSprite(&template, 272, 144, 10);
        template.tileTag++;
    }

    gSprites[spriteIds[0]].data[0] = spriteIds[1];
    gSprites[spriteIds[0]].data[1] = spriteIds[2];
    gSprites[spriteIds[0]].data[2] = spriteIds[3];

    gSprites[spriteIds[4]].data[0] = spriteIds[5];
    gSprites[spriteIds[4]].data[1] = spriteIds[6];
    gSprites[spriteIds[4]].data[2] = spriteIds[7];

    gUnknown_0203A034->unk0->unk0 = spriteIds[0];
    gUnknown_0203A034->unk0->unk4 = 0;
    gUnknown_0203A034->unk0->unk1 = spriteIds[4];
    sub_80F7144();
}

static void sub_80F6E9C(s16 arg0, u16 y, u16 arg2, u16 arg3)
{
    struct Sprite *sprite = &gSprites[gUnknown_0203A034->unk0->unk0];
    sprite->pos1.x = 272;
    sprite->pos1.y = y;
    sprite->pos2.x = 0;
    sprite->pos2.y = 0;
    sprite->data[4] = arg0 + 32;
    sprite->data[5] = arg2;
    sprite->data[6] = arg3;
    sprite->data[7] = 0;
    sprite->callback = sub_80F6F68;
    gUnknown_0203A034->unk0->unk4 = 1;
}

static void sub_80F6EF4(u16 arg0)
{
    struct Sprite *sprite = &gSprites[gUnknown_0203A034->unk0->unk0];
    sprite->pos1.x += sprite->pos2.x;
    sprite->pos1.y += sprite->pos2.y;
    sprite->pos2.y = 0;
    sprite->pos2.x = 0;
    sprite->data[6] = arg0;
    sprite->data[7] = 0;
    sprite->callback = sub_80F7014;
    gUnknown_0203A034->unk0->unk4 = 3;
}

static void sub_80F6F40(struct Sprite *sprite)
{
    sprite->pos1.x = 272;
    sprite->pos1.y = 144;
    sprite->pos2.y = 0;
    sprite->pos2.x = 0;
    sprite->callback = SpriteCallbackDummy;
    gUnknown_0203A034->unk0->unk4 = 0;
}

static void sub_80F6F68(struct Sprite *sprite)
{
    int i;
    s16 var0;

    var0 = (u16)sprite->data[7] + (u16)sprite->data[6];
    sprite->pos1.x -= var0 >> 8;
    sprite->data[7] = (sprite->data[6] + sprite->data[7]) & 0xFF;
    if (sprite->pos1.x < sprite->data[4])
        sprite->pos1.x = sprite->data[4];

    for (i = 0; i < 3; i++)
    {
        struct Sprite *sprite2 = &gSprites[sprite->data[i]];
        sprite2->pos1.x = sprite->pos1.x + sprite->pos2.x + (i + 1) * 64;
    }

    if (sprite->pos1.x == sprite->data[4])
        sprite->callback = sub_80F6FDC;
}

static void sub_80F6FDC(struct Sprite *sprite)
{
    gUnknown_0203A034->unk0->unk4 = 2;
    if ((u16)sprite->data[5] != 0xFFFF)
    {
        if (--sprite->data[5] == -1)
            sub_80F6EF4(sprite->data[6]);
    }
}

static void sub_80F7014(struct Sprite *sprite)
{
    int i;
    s16 var0;

    var0 = (u16)sprite->data[7] + (u16)sprite->data[6];
    sprite->pos1.x -= var0 >> 8;
    sprite->data[7] = (sprite->data[6] + sprite->data[7]) & 0xFF;
    for (i = 0; i < 3; i++)
    {
        struct Sprite *sprite2 = &gSprites[sprite->data[i]];
        sprite2->pos1.x = sprite->pos1.x + sprite->pos2.x + (i + 1) * 64;
    }

    if (sprite->pos1.x + sprite->pos2.x < -224)
        sub_80F6F40(sprite);
}

static void sub_80F707C(const u8 *text)
{
    int i;
    u16 x;
    struct Sprite *sprite;

    x = sub_80F6B78(text, gUnknown_0203A034->unk0->unk1);
    sprite = &gSprites[gUnknown_0203A034->unk0->unk1];
    sprite->pos1.x = x + 32;
    sprite->pos1.y = 80;
    sprite->invisible = 0;
    for (i = 0; i < 3; i++)
    {
        gSprites[sprite->data[i]].pos1.x = sprite->pos1.x + sprite->pos2.x + (i + 1) * 64;
        gSprites[sprite->data[i]].pos1.y = sprite->pos1.y;
        gSprites[sprite->data[i]].invisible = 0;
    }

    gBattle_WIN0H = 0x00F0;
    gBattle_WIN0V = ((sprite->pos1.y - 16) << 8) | (sprite->pos1.y + 16);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR
        | WININ_WIN0_BG1 | WININ_WIN0_BG2 | WININ_WIN0_BG3 | WININ_WIN0_OBJ | WININ_WIN0_CLR);
}

static void sub_80F7144(void)
{
    int i;
    struct Sprite *sprite;

    sprite = &gSprites[gUnknown_0203A034->unk0->unk1];
    sprite->invisible = 1;
    for (i = 0; i < 3; i++)
        gSprites[sprite->data[i]].invisible = 1;

    gBattle_WIN0H = 0;
    gBattle_WIN0V = 0;
    SetGpuReg(REG_OFFSET_WIN0H, gBattle_WIN0H);
    SetGpuReg(REG_OFFSET_WIN0V, gBattle_WIN0V);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN0_CLR
        | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ | WININ_WIN1_CLR);
}

static void sub_80F71C8(void)
{
    u8 palette;
    int x, y;

    x = 5;
    y = 1;
    if (gIsLinkContest & 0x1)
    {
        CopyToBgTilemapBufferRect(2, gUnknown_08DC6498, 5, 1, 5, 2);
        x = 10;
    }
    else if (gSpecialVar_ContestRank == 0)
    {
        CopyToBgTilemapBufferRect(2, gUnknown_08DC63F8, 5, 1, 10, 2);
        x = 15;
    }
    else if (gSpecialVar_ContestRank == 1)
    {
        CopyToBgTilemapBufferRect(2, gUnknown_08DC6420, 5, 1, 10, 2);
        x = 15;
    }
    else if (gSpecialVar_ContestRank == 2)
    {
        CopyToBgTilemapBufferRect(2, gUnknown_08DC6448, 5, 1, 10, 2);
        x = 15;
    }
    else
    {
        CopyToBgTilemapBufferRect(2, gUnknown_08DC6470, 5, 1, 10, 2);
        x = 15;
    }

    if (gSpecialVar_ContestCategory == 0)
    {
        palette = 0;
        CopyToBgTilemapBufferRect(2, gUnknown_08DC64AC, x, y, 5, 2);
    }
    else if (gSpecialVar_ContestCategory == 1)
    {
        palette = 1;
        CopyToBgTilemapBufferRect(2, gUnknown_08DC64C0, x, y, 5, 2);
    }
    else if (gSpecialVar_ContestCategory == 2)
    {
        palette = 2;
        CopyToBgTilemapBufferRect(2, gUnknown_08DC64D4, x, y, 5, 2);
    }
    else if (gSpecialVar_ContestCategory == 3)
    {
        palette = 3;
        CopyToBgTilemapBufferRect(2, gUnknown_08DC64E8, x, y, 5, 2);
    }
    else
    {
        palette = 4;
        CopyToBgTilemapBufferRect(2, gUnknown_08DC64FC, x, y, 5, 2);
    }

    x += 5;
    CopyToBgTilemapBufferRect(2, gUnknown_08DC6510, x, y, 6, 2);
    CopyToBgTilemapBufferRect_ChangePalette(2, gUnknown_0203A034->unkC[2], 0, 0, 32, 4, palette);
}

// fakematching?
u8 sub_80F7310(u8 monIndex, u8 arg1)
{
    u32 var0;
    u32 var1;

    var0 = gContestMonConditions[monIndex] << 16;
    var1 = var0 / 0x3F;
    if (var1 & 0xFFFF)
        var1 += 0x10000;

    var1 >>= 16;
    if (var1 == 0 && var0)
        var1 = 1;

    if (arg1 && var1 > 10)
        var1 = 10;

    return var1;
}

s8 sub_80F7364(u8 arg0, u8 arg1)
{
    u32 r4;
    u32 r2;
    s16 val;
    s8 ret;

    val = gUnknown_02039F18[arg0];
    if (val < 0)
        r4 = -val << 16;
    else
        r4 = val << 16;

    r2 = r4 / 80;
    if (r2 & 0xFFFF)
        r2 += 0x10000;

    r2 >>= 16;
    if (r2 == 0 && r4 != 0)
        r2 = 1;

    if (arg1 != 0 && r2 > 10)
        r2 = 10;

    if (gUnknown_02039F18[arg0] < 0)
        ret = -r2;
    else
        ret = r2;

    return ret;
}

static void sub_80F73DC(u8 taskId)
{
    u16 firstTileNum;

    if (gTasks[taskId].data[10] == 0)
    {
        gTasks[taskId].data[11] = (3 - gTasks[taskId].data[0]) * 40;
        gTasks[taskId].data[10]++;
    }
    else if (gTasks[taskId].data[10] == 1)
    {
        if (--gTasks[taskId].data[11] == -1)
        {
            firstTileNum = gTasks[taskId].data[0] * 2 + 0x5043;
            WriteSequenceToBgTilemapBuffer(2, firstTileNum, 1, gTasks[taskId].data[1] * 3 + 5, 2, 1, 17, 1);
            WriteSequenceToBgTilemapBuffer(2, firstTileNum + 0x10, 1, gTasks[taskId].data[1] * 3 + 6, 2, 1, 17, 1);
            gUnknown_0203A034->unk0->unk5++;
            DestroyTask(taskId);
            PlaySE(SE_JYUNI);
        }
    }
}

static void sub_80F74BC(u8 taskId)
{
    int i;
    for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
        ;

    CopyToBgTilemapBufferRect_ChangePalette(2, i * 0xC0 + 0x100 + gUnknown_0203A034->unkC[2], 0, i * 3 + 4, 32, 3, 9);
    gTasks[taskId].data[10] = i;
    gTasks[taskId].data[12] = 1;
    gTasks[taskId].func = sub_80F753C;
    gUnknown_0203A034->unk0->unk3 = taskId;
}

static void sub_80F753C(u8 taskId)
{
    if (++gTasks[taskId].data[11] == 1)
    {
        gTasks[taskId].data[11] = 0;
        BlendPalette(0x91, 1, gTasks[taskId].data[12], RGB(13, 28, 27));
        if (gTasks[taskId].data[13] == 0)
        {
            if (++gTasks[taskId].data[12] == 16)
                gTasks[taskId].data[13] = 1;
        }
        else
        {
            if (--gTasks[taskId].data[12] == 0)
                gTasks[taskId].data[13] = 0;
        }
    }
}

static void sub_80F75A8(struct Sprite *sprite)
{
    if (sprite->data[0] < 10)
    {
        if (++sprite->data[0] == 10)
        {
            PlayCry1(sprite->data[1], 0);
            sprite->data[1] = 0;
        }
    }
    else
    {
        s16 delta = (u16)sprite->data[1] + 0x600;
        sprite->pos1.x -= delta >> 8;
        sprite->data[1] = (sprite->data[1] + 0x600) & 0xFF;
        if (sprite->pos1.x < 120)
            sprite->pos1.x = 120;

        if (sprite->pos1.x == 120)
        {
            sprite->callback = SpriteCallbackDummy;
            sprite->data[1] = 0;
            gUnknown_0203A034->unk0->unk6 = 1;
        }
    }
}

static void sub_80F7620(struct Sprite *sprite)
{
    s16 delta = (u16)sprite->data[1] + 0x600;
    sprite->pos1.x -= delta >> 8;
    sprite->data[1] = (sprite->data[1] + 0x600) & 0xFF;
    if (sprite->pos1.x < -32)
    {
        sprite->callback = SpriteCallbackDummy;
        sprite->invisible = 1;
        gUnknown_0203A034->unk0->unk6 = 2;
    }
}

static void sub_80F7670(u8 taskId)
{
    if (++gTasks[taskId].data[0] == 5)
    {
        gTasks[taskId].data[0] = 0;
        if (gUnknown_0203A034->unk0->unk7 < 40)
        {
            u8 spriteId = CreateSprite(&gSpriteTemplate_858D860, (Random() % 240) - 20, 44, 5);
            gSprites[spriteId].data[0] = Random() % 512;
            gSprites[spriteId].data[1] = (Random() % 24) + 16;
            gSprites[spriteId].data[2] = (Random() % 256) + 48;
            gSprites[spriteId].oam.tileNum += Random() % 17;
            gUnknown_0203A034->unk0->unk7++;
        }
    }

    if (gUnknown_0203A034->unk0->unk9)
        DestroyTask(taskId);
}

void sub_80F7768(struct Sprite *sprite)
{
    register s16 var0 asm("r1");

    sprite->data[3] += sprite->data[0];
    sprite->pos2.x = Sin(sprite->data[3] >> 8, sprite->data[1]);
    var0 = sprite->data[4] + sprite->data[2];
    sprite->pos1.x += var0 >> 8;
    var0 = var0 & 0xFF;
    sprite->data[4] = var0;
    sprite->pos1.y++;
    if (gUnknown_0203A034->unk0->unk9)
        sprite->invisible = 1;
    
    if (sprite->pos1.x > 248 || sprite->pos1.y > 116)
    {
        DestroySprite(sprite);
        gUnknown_0203A034->unk0->unk7--;
    }
}

static void sub_80F77E0(u8 monIndex, u8 numFrames)
{
    u8 taskId = CreateTask(sub_80F7824, 8);
    gTasks[taskId].data[0] = monIndex;
    gTasks[taskId].data[1] = numFrames;
    gTasks[taskId].data[2] = gContestMons[monIndex].species;
}

static void sub_80F7824(u8 taskId)
{
    u8 monIndex = gTasks[taskId].data[0];
    if (gTasks[taskId].data[10]++ == gTasks[taskId].data[1])
    {
        gTasks[taskId].data[10] = 0;
        sub_80F69B8(gTasks[taskId].data[2], monIndex, gTasks[taskId].data[11], FALSE, gContestMons[monIndex].personality);
        gTasks[taskId].data[11] ^= 1;
    }
}

// static void sub_80F7880(void)
// {
//     int i;
//     int var0;
//     int var1;
//     int var2;
//     int var3;
//     u32 var4;
//     int var5;
//     int var6;
//     s16 var7;
//     s16 var8;
//     s16 r2;

//     r2 = gUnknown_02039F08[0];
//     for (i = 1; i < 4; i++)
//     {
//         if (r2 < gUnknown_02039F08[i])
//             r2 = gUnknown_02039F08[i];
//     }

//     if (r2 < 0)
//     {
//         r2 = gUnknown_02039F08[0];
//         for (i = 1; i < 4; i++)
//         {
//             if (r2 > gUnknown_02039F08[i])
//                 r2 = gUnknown_02039F08[i];
//         }
//     }

//     // _080F78E4
//     for (i = 0; i < 4; i++)
//     {
//         var0 = gContestMonConditions[i] * 1000;
//         var1 = r2;
//         if (r2 < 0)
//             var1 = -var1;

//         var2 = var0 / var1;
//         if (var2 % 10 > 4)
//             var2 += 10;

//         gUnknown_0203A034->unk4->unk0[i].unk0 = var2 / 10;
//         var3 = gUnknown_02039F18[i];
//         if (var3 < 0)
//             var3 = -var3;

//         var0 = var3 * 1000;
//         var1 = r2;
//         if (r2 < 0)
//             var1 = -var1;

//         var2 = var0 / var1;
//         if (var2 % 10 > 4)
//             var2 += 10;

//         // _080F7966
//         gUnknown_0203A034->unk4->unk0[i].unk4 = var2 / 10;
//         if (gUnknown_02039F18[i] < 0)
//             gUnknown_0203A034->unk4->unk0[i].unk10 = 1;

//         var4 = gUnknown_0203A034->unk4->unk0[i].unk0 * 22528 / 100;
//         if ((var4 & 0xFF) > 0x7F)
//             var4 += 0x100;

//         gUnknown_0203A034->unk4->unk0[i].unk8 = var4 >> 8;
//         var4 = gUnknown_0203A034->unk4->unk0[i].unk4 * 22528 / 100;
//         if ((var4 & 0xFF) > 0x7F)
//             var4 += 0x100;

//         gUnknown_0203A034->unk4->unk0[i].unkC = var4 >> 8;
//         gUnknown_0203A034->unk4->unk0[i].unk11 = sub_80F7310(i, 1);
//         var5 = sub_80F7364(i, 1);
//         if (var5 < 0)
//             var5 = -var5;

//         gUnknown_0203A034->unk4->unk0[i].unk12 = var5;
//         if (gContestFinalStandings[i])
//         {
//             var7 = gUnknown_0203A034->unk4->unk0[i].unk8;
//             var8 = gUnknown_0203A034->unk4->unk0[i].unkC;
//             if (gUnknown_0203A034->unk4->unk0[i].unk10)
//                 var8 = -var8;

//             if (var7 + var8 == 88)
//             {
//                 if (var8 > 0)
//                     gUnknown_0203A034->unk4->unk0[i].unkC--;
//                 else if (var7 > 0)
//                     gUnknown_0203A034->unk4->unk0[i].unk8--;
//             }
//         }
//     }
// }

NAKED
static void sub_80F7880(void)
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0x4\n\
    ldr r0, =gUnknown_02039F08\n\
    ldrh r2, [r0]\n\
    adds r4, r0, 0\n\
    adds r3, r4, 0x2\n\
    movs r0, 0x2\n\
    mov r8, r0\n\
_080F7898:\n\
    lsls r0, r2, 16\n\
    asrs r0, 16\n\
    movs r5, 0\n\
    ldrsh r1, [r3, r5]\n\
    cmp r0, r1\n\
    bge _080F78A6\n\
    ldrh r2, [r3]\n\
_080F78A6:\n\
    adds r3, 0x2\n\
    movs r0, 0x1\n\
    negs r0, r0\n\
    add r8, r0\n\
    mov r1, r8\n\
    cmp r1, 0\n\
    bge _080F7898\n\
    lsls r0, r2, 16\n\
    str r0, [sp]\n\
    cmp r0, 0\n\
    bge _080F78E4\n\
    ldrh r2, [r4]\n\
    adds r3, r4, 0x2\n\
    movs r4, 0x2\n\
    mov r8, r4\n\
_080F78C4:\n\
    lsls r0, r2, 16\n\
    asrs r0, 16\n\
    movs r5, 0\n\
    ldrsh r1, [r3, r5]\n\
    cmp r0, r1\n\
    ble _080F78D2\n\
    ldrh r2, [r3]\n\
_080F78D2:\n\
    adds r3, 0x2\n\
    movs r0, 0x1\n\
    negs r0, r0\n\
    add r8, r0\n\
    lsls r1, r2, 16\n\
    str r1, [sp]\n\
    mov r4, r8\n\
    cmp r4, 0\n\
    bge _080F78C4\n\
_080F78E4:\n\
    movs r5, 0\n\
    mov r8, r5\n\
    mov r10, r5\n\
_080F78EA:\n\
    ldr r0, =gContestMonConditions\n\
    mov r1, r8\n\
    lsls r7, r1, 1\n\
    adds r0, r7, r0\n\
    movs r2, 0\n\
    ldrsh r1, [r0, r2]\n\
    lsls r0, r1, 5\n\
    subs r0, r1\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    lsls r0, 3\n\
    ldr r4, [sp]\n\
    asrs r5, r4, 16\n\
    adds r1, r5, 0\n\
    cmp r5, 0\n\
    bge _080F790C\n\
    negs r1, r5\n\
_080F790C:\n\
    bl __divsi3\n\
    adds r4, r0, 0\n\
    movs r1, 0xA\n\
    bl __modsi3\n\
    cmp r0, 0x4\n\
    ble _080F791E\n\
    adds r4, 0xA\n\
_080F791E:\n\
    ldr r0, =gUnknown_0203A034\n\
    mov r9, r0\n\
    ldr r0, [r0]\n\
    ldr r0, [r0, 0x4]\n\
    mov r1, r10\n\
    adds r6, r1, r0\n\
    adds r0, r4, 0\n\
    movs r1, 0xA\n\
    bl __divsi3\n\
    str r0, [r6]\n\
    ldr r0, =gUnknown_02039F18\n\
    adds r7, r0\n\
    movs r2, 0\n\
    ldrsh r1, [r7, r2]\n\
    cmp r1, 0\n\
    bge _080F7942\n\
    negs r1, r1\n\
_080F7942:\n\
    lsls r0, r1, 5\n\
    subs r0, r1\n\
    lsls r0, 2\n\
    adds r0, r1\n\
    lsls r0, 3\n\
    adds r1, r5, 0\n\
    cmp r1, 0\n\
    bge _080F7954\n\
    negs r1, r1\n\
_080F7954:\n\
    bl __divsi3\n\
    adds r4, r0, 0\n\
    movs r1, 0xA\n\
    bl __modsi3\n\
    cmp r0, 0x4\n\
    ble _080F7966\n\
    adds r4, 0xA\n\
_080F7966:\n\
    adds r0, r4, 0\n\
    movs r1, 0xA\n\
    bl __divsi3\n\
    str r0, [r6, 0x4]\n\
    movs r4, 0\n\
    ldrsh r0, [r7, r4]\n\
    cmp r0, 0\n\
    bge _080F797C\n\
    movs r0, 0x1\n\
    strb r0, [r6, 0x10]\n\
_080F797C:\n\
    mov r5, r9\n\
    ldr r0, [r5]\n\
    ldr r0, [r0, 0x4]\n\
    mov r1, r10\n\
    adds r4, r1, r0\n\
    ldr r1, [r4]\n\
    lsls r0, r1, 1\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    subs r0, r1\n\
    lsls r0, 11\n\
    movs r1, 0x64\n\
    bl __divsi3\n\
    adds r1, r0, 0\n\
    movs r5, 0xFF\n\
    ands r0, r5\n\
    cmp r0, 0x7F\n\
    bls _080F79A8\n\
    movs r2, 0x80\n\
    lsls r2, 1\n\
    adds r1, r2\n\
_080F79A8:\n\
    lsrs r0, r1, 8\n\
    str r0, [r4, 0x8]\n\
    ldr r1, [r4, 0x4]\n\
    lsls r0, r1, 1\n\
    adds r0, r1\n\
    lsls r0, 2\n\
    subs r0, r1\n\
    lsls r0, 11\n\
    movs r1, 0x64\n\
    bl __divsi3\n\
    adds r1, r0, 0\n\
    ands r0, r5\n\
    cmp r0, 0x7F\n\
    bls _080F79CC\n\
    movs r5, 0x80\n\
    lsls r5, 1\n\
    adds r1, r5\n\
_080F79CC:\n\
    lsrs r0, r1, 8\n\
    str r0, [r4, 0xC]\n\
    mov r0, r8\n\
    lsls r4, r0, 24\n\
    lsrs r4, 24\n\
    adds r0, r4, 0\n\
    movs r1, 0x1\n\
    bl sub_80F7310\n\
    mov r2, r9\n\
    ldr r1, [r2]\n\
    ldr r1, [r1, 0x4]\n\
    add r1, r10\n\
    strb r0, [r1, 0x11]\n\
    adds r0, r4, 0\n\
    movs r1, 0x1\n\
    bl sub_80F7364\n\
    mov r4, r9\n\
    ldr r1, [r4]\n\
    ldr r1, [r1, 0x4]\n\
    add r1, r10\n\
    lsls r0, 24\n\
    asrs r0, 24\n\
    cmp r0, 0\n\
    bge _080F7A02\n\
    negs r0, r0\n\
_080F7A02:\n\
    strb r0, [r1, 0x12]\n\
    ldr r0, =gContestFinalStandings\n\
    add r0, r8\n\
    ldrb r0, [r0]\n\
    cmp r0, 0\n\
    beq _080F7A60\n\
    mov r5, r9\n\
    ldr r0, [r5]\n\
    ldr r0, [r0, 0x4]\n\
    mov r2, r10\n\
    adds r1, r2, r0\n\
    ldr r5, [r1, 0x8]\n\
    ldrh r3, [r1, 0x8]\n\
    ldr r4, [r1, 0xC]\n\
    ldrh r2, [r1, 0xC]\n\
    ldrb r0, [r1, 0x10]\n\
    cmp r0, 0\n\
    beq _080F7A2C\n\
    lsls r0, r2, 16\n\
    negs r0, r0\n\
    lsrs r2, r0, 16\n\
_080F7A2C:\n\
    lsls r0, r3, 16\n\
    asrs r3, r0, 16\n\
    lsls r0, r2, 16\n\
    asrs r2, r0, 16\n\
    adds r0, r3, r2\n\
    cmp r0, 0x58\n\
    bne _080F7A60\n\
    cmp r2, 0\n\
    ble _080F7A58\n\
    subs r0, r4, 0x1\n\
    str r0, [r1, 0xC]\n\
    b _080F7A60\n\
    .pool\n\
_080F7A58:\n\
    cmp r3, 0\n\
    ble _080F7A60\n\
    subs r0, r5, 0x1\n\
    str r0, [r1, 0x8]\n\
_080F7A60:\n\
    movs r4, 0x14\n\
    add r10, r4\n\
    movs r5, 0x1\n\
    add r8, r5\n\
    mov r0, r8\n\
    cmp r0, 0x3\n\
    bgt _080F7A70\n\
    b _080F78EA\n\
_080F7A70:\n\
    add sp, 0x4\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0");
}

// static void sub_80F7A80(u8 arg0, u8 arg1)
// {
//     int i;
//     u8 taskId;
//     u8 sp8, spC;

//     sp8 = 0;
//     spC = 0;
//     if (!arg0)
//     {
//         u32 var0;
//         for (i = 0; i < 4; i++)
//         {
//             int var1 = gUnknown_0203A034->unk4->unk0[i].unk11;
//             if (arg1 < var1)
//             {
//                 int x = var1 + 19;
//                 x -= arg1;
//                 x--;
//                 FillBgTilemapBufferRect_Palette0(1, 0x60B3, x, i * 3 + 5, 1, 1);
//                 taskId = CreateTask(sub_80F7CA8, 10);
//                 var0 = ((gUnknown_0203A034->unk4->unk0[i].unk8 << 16) / gUnknown_0203A034->unk4->unk0[i].unk11) * (arg1 + 1);
//                 var0 &= 0xFFFF;
//                 if (var0 > 0x7FFF)
//                     var0 += 0x10000;

//                 gTasks[taskId].data[0] = i;
//                 gTasks[taskId].data[1] = var0 >> 16;
//                 gUnknown_0203A034->unk0->unk14++;
//                 sp8++;
//             }
//         }
//     }
//     else
//     {
//         u32 var0;
//         for (i = 0; i < 4; i++)
//         {
//             int tile;
//             s8 var1 = gUnknown_0203A034->unk4->unk0[i].unk12;
//             tile = gUnknown_0203A034->unk4->unk0[i].unk10 ? 0x60A5 : 0x60A3;
//             if (arg1 < var1)
//             {
//                 int thing = ((s8)arg1 - 19);
//                 int x = var1 - thing;
//                 x--;
//                 FillBgTilemapBufferRect_Palette0(1, tile, x, i * 3 + 6, 1, 1);
//                 taskId = CreateTask(sub_80F7CA8, 10);
//                 var0 = ((gUnknown_0203A034->unk4->unk0[i].unkC << 16) / gUnknown_0203A034->unk4->unk0[i].unk12) * (arg1 + 1);
//                 var0 &= 0xFFFF;
//                 if (var0 > 0x7FFF)
//                     var0 += 0x10000;

//                 gTasks[taskId].data[0] = i;
//                 if (gUnknown_0203A034->unk4->unk0[i].unk10)
//                 {
//                     gTasks[taskId].data[2] = 1;
//                     spC++;
//                 }
//                 else
//                 {
//                     sp8++;
//                 }

//                 if (gUnknown_0203A034->unk4->unk0[i].unk10)
//                     gTasks[taskId].data[1] = gUnknown_0203A034->unk4->unk0[i].unk8 - (var0 >> 16);
//                 else
//                     gTasks[taskId].data[1] = gUnknown_0203A034->unk4->unk0[i].unk8 + (var0 >> 16);

//                 gUnknown_0203A034->unk0->unk14++;
//             }
//         }
//     }

//     if (spC)
//         PlaySE(SE_PIN);
    
//     if (sp8)
//         PlaySE(SE_BAN);
// }

NAKED
static void sub_80F7A80(u8 arg0, u8 arg1)
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r10\n\
    mov r6, r9\n\
    mov r5, r8\n\
    push {r5-r7}\n\
    sub sp, 0x14\n\
    lsls r0, 24\n\
    lsls r1, 24\n\
    lsrs r1, 24\n\
    mov r8, r1\n\
    movs r1, 0\n\
    str r1, [sp, 0x8]\n\
    movs r3, 0\n\
    str r3, [sp, 0xC]\n\
    cmp r0, 0\n\
    bne _080F7B5C\n\
    mov r9, r3\n\
    ldr r4, =gUnknown_0203A034\n\
    mov r10, r4\n\
    movs r7, 0xA0\n\
    lsls r7, 19\n\
    movs r6, 0\n\
_080F7AAC:\n\
    mov r1, r10\n\
    ldr r0, [r1]\n\
    ldr r0, [r0, 0x4]\n\
    adds r0, r6, r0\n\
    ldrb r2, [r0, 0x11]\n\
    cmp r8, r2\n\
    bcs _080F7B2E\n\
    adds r2, 0x13\n\
    mov r3, r8\n\
    subs r2, r3\n\
    subs r2, 0x1\n\
    lsls r2, 24\n\
    lsrs r2, 24\n\
    lsrs r3, r7, 24\n\
    movs r0, 0x1\n\
    str r0, [sp]\n\
    str r0, [sp, 0x4]\n\
    ldr r1, =0x000060b3\n\
    bl FillBgTilemapBufferRect_Palette0\n\
    ldr r0, =sub_80F7CA8\n\
    movs r1, 0xA\n\
    bl CreateTask\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    mov r0, r10\n\
    ldr r4, [r0]\n\
    ldr r1, [r4, 0x4]\n\
    adds r1, r6, r1\n\
    ldr r0, [r1, 0x8]\n\
    lsls r0, 16\n\
    ldrb r1, [r1, 0x11]\n\
    bl __udivsi3\n\
    mov r1, r8\n\
    adds r1, 0x1\n\
    adds r3, r0, 0\n\
    muls r3, r1\n\
    ldr r0, =0x0000ffff\n\
    ands r0, r3\n\
    ldr r1, =0x00007fff\n\
    cmp r0, r1\n\
    bls _080F7B0A\n\
    movs r1, 0x80\n\
    lsls r1, 9\n\
    adds r3, r1\n\
_080F7B0A:\n\
    ldr r1, =gTasks\n\
    lsls r0, r5, 2\n\
    adds r0, r5\n\
    lsls r0, 3\n\
    adds r0, r1\n\
    mov r1, r9\n\
    strh r1, [r0, 0x8]\n\
    lsrs r1, r3, 16\n\
    strh r1, [r0, 0xA]\n\
    ldr r1, [r4]\n\
    ldrb r0, [r1, 0x14]\n\
    adds r0, 0x1\n\
    strb r0, [r1, 0x14]\n\
    ldr r0, [sp, 0x8]\n\
    adds r0, 0x1\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    str r0, [sp, 0x8]\n\
_080F7B2E:\n\
    movs r3, 0xC0\n\
    lsls r3, 18\n\
    adds r7, r3\n\
    adds r6, 0x14\n\
    movs r4, 0x1\n\
    add r9, r4\n\
    mov r0, r9\n\
    cmp r0, 0x3\n\
    ble _080F7AAC\n\
    b _080F7C7E\n\
    .pool\n\
_080F7B5C:\n\
    movs r1, 0\n\
    mov r9, r1\n\
    mov r10, r1\n\
    movs r3, 0xC0\n\
    lsls r3, 19\n\
    str r3, [sp, 0x10]\n\
_080F7B68:\n\
    ldr r4, =gUnknown_0203A034\n\
    ldr r0, [r4]\n\
    ldr r0, [r0, 0x4]\n\
    add r0, r10\n\
    ldrb r2, [r0, 0x12]\n\
    ldrb r0, [r0, 0x10]\n\
    ldr r1, =0x000060a3\n\
    cmp r0, 0\n\
    beq _080F7B7C\n\
    adds r1, 0x2\n\
_080F7B7C:\n\
    lsls r0, r2, 24\n\
    asrs r0, 24\n\
    cmp r8, r0\n\
    bge _080F7C64\n\
    mov r3, r8\n\
    lsls r2, r3, 24\n\
    asrs r2, 24\n\
    subs r2, 0x13\n\
    subs r2, r0, r2\n\
    subs r2, 0x1\n\
    lsls r2, 24\n\
    lsrs r2, 24\n\
    ldr r4, [sp, 0x10]\n\
    lsrs r3, r4, 24\n\
    movs r7, 0x1\n\
    str r7, [sp]\n\
    str r7, [sp, 0x4]\n\
    movs r0, 0x1\n\
    bl FillBgTilemapBufferRect_Palette0\n\
    ldr r0, =sub_80F7CA8\n\
    movs r1, 0xA\n\
    bl CreateTask\n\
    lsls r0, 24\n\
    lsrs r5, r0, 24\n\
    ldr r0, =gUnknown_0203A034\n\
    ldr r6, [r0]\n\
    ldr r1, [r6, 0x4]\n\
    add r1, r10\n\
    ldr r0, [r1, 0xC]\n\
    lsls r0, 16\n\
    ldrb r1, [r1, 0x12]\n\
    bl __udivsi3\n\
    mov r1, r8\n\
    adds r1, 0x1\n\
    adds r3, r0, 0\n\
    muls r3, r1\n\
    ldr r0, =0x0000ffff\n\
    ands r0, r3\n\
    ldr r1, =0x00007fff\n\
    cmp r0, r1\n\
    bls _080F7BDA\n\
    movs r1, 0x80\n\
    lsls r1, 9\n\
    adds r3, r1\n\
_080F7BDA:\n\
    ldr r1, =gTasks\n\
    lsls r2, r5, 2\n\
    adds r0, r2, r5\n\
    lsls r0, 3\n\
    adds r4, r0, r1\n\
    mov r0, r9\n\
    strh r0, [r4, 0x8]\n\
    ldr r0, [r6, 0x4]\n\
    add r0, r10\n\
    ldrb r0, [r0, 0x10]\n\
    adds r6, r1, 0\n\
    cmp r0, 0\n\
    beq _080F7C1C\n\
    strh r7, [r4, 0xC]\n\
    ldr r0, [sp, 0xC]\n\
    adds r0, 0x1\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    str r0, [sp, 0xC]\n\
    b _080F7C26\n\
    .pool\n\
_080F7C1C:\n\
    ldr r0, [sp, 0x8]\n\
    adds r0, 0x1\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    str r0, [sp, 0x8]\n\
_080F7C26:\n\
    ldr r1, =gUnknown_0203A034\n\
    ldr r0, [r1]\n\
    ldr r0, [r0, 0x4]\n\
    mov r4, r10\n\
    adds r1, r4, r0\n\
    ldrb r0, [r1, 0x10]\n\
    ldr r4, =gUnknown_0203A034\n\
    cmp r0, 0\n\
    beq _080F7C4C\n\
    adds r0, r2, r5\n\
    lsls r0, 3\n\
    adds r0, r6\n\
    lsrs r2, r3, 16\n\
    ldr r1, [r1, 0x8]\n\
    subs r1, r2\n\
    b _080F7C58\n\
    .pool\n\
_080F7C4C:\n\
    adds r0, r2, r5\n\
    lsls r0, 3\n\
    adds r0, r6\n\
    lsrs r2, r3, 16\n\
    ldr r1, [r1, 0x8]\n\
    adds r1, r2\n\
_080F7C58:\n\
    strh r1, [r0, 0xA]\n\
    ldr r0, [r4]\n\
    ldr r1, [r0]\n\
    ldrb r0, [r1, 0x14]\n\
    adds r0, 0x1\n\
    strb r0, [r1, 0x14]\n\
_080F7C64:\n\
    movs r0, 0x14\n\
    add r10, r0\n\
    ldr r1, [sp, 0x10]\n\
    movs r3, 0xC0\n\
    lsls r3, 18\n\
    adds r1, r3\n\
    str r1, [sp, 0x10]\n\
    movs r4, 0x1\n\
    add r9, r4\n\
    mov r0, r9\n\
    cmp r0, 0x3\n\
    bgt _080F7C7E\n\
    b _080F7B68\n\
_080F7C7E:\n\
    ldr r1, [sp, 0xC]\n\
    cmp r1, 0\n\
    beq _080F7C8A\n\
    movs r0, 0x16\n\
    bl PlaySE\n\
_080F7C8A:\n\
    ldr r3, [sp, 0x8]\n\
    cmp r3, 0\n\
    beq _080F7C96\n\
    movs r0, 0x15\n\
    bl PlaySE\n\
_080F7C96:\n\
    add sp, 0x14\n\
    pop {r3-r5}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    mov r10, r5\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0");
}

#ifdef NONMATCHING
void sub_80F7CA8(u8 taskId)
{
    register int r4 asm("r4");
    int r9;
    u8 r6;
    s16 r7;
    s16 r12;
    int i;
    u8 var0;
    u16 tileNum;

    r4 = 0;
    r9 = 0;
    r6 = gTasks[taskId].data[0]; 
    r7 = gTasks[taskId].data[1];
    r12 = gTasks[taskId].data[2];
    if (r12)
    {
        if (gUnknown_0203A034->unk0->unkC[r6] <= 0)
            r4 = 1;
    }
    else
    {
        if (gUnknown_0203A034->unk0->unkC[r6] > 87)
            r4 = 1;
    }

    if (gUnknown_0203A034->unk0->unkC[r6] == r7)
        r9 = 1;

    if (!r9)
    {
        if (r4)
            gUnknown_0203A034->unk0->unkC[r6] = r7;
        else if (r12)
            gUnknown_0203A034->unk0->unkC[r6] = gUnknown_0203A034->unk0->unkC[r6] - 1;
        else
            gUnknown_0203A034->unk0->unkC[r6] = gUnknown_0203A034->unk0->unkC[r6] + 1;
    }

    if (!r4 && !r9)
    {
        for (i = 0; i < 11; i++)
        {
            if (gUnknown_0203A034->unk0->unkC[r6] >= (i + 1) * 8)
            {
                var0 = 8;
            }
            else if (gUnknown_0203A034->unk0->unkC[r6] >= i * 8)
            {
                int var2 = gUnknown_0203A034->unk0->unkC[r6];
                int var1 = var2;
                if (var1 < 0)
                    var1 += 7;

                var0 = var2 - ((var1 >> 3) << 3);
            }
            else
            {
                var0 = 0;
            }

            if (var0 < 4)
                tileNum = 0x504C;
            else
                tileNum = 0x5057;

            FillBgTilemapBufferRect_Palette0(2, tileNum + var0, i + 7, r6 * 3 + 6, 1, 1);
        }
    }
    
    if (r9)
    {
        gUnknown_0203A034->unk0->unk14--;
        DestroyTask(taskId);
    }
}
#else
NAKED
void sub_80F7CA8(u8 taskId)
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r9\n\
    mov r6, r8\n\
    push {r6,r7}\n\
    sub sp, 0x8\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    mov r8, r0\n\
    movs r4, 0\n\
    mov r9, r4\n\
    ldr r1, =gTasks\n\
    lsls r0, 2\n\
    add r0, r8\n\
    lsls r0, 3\n\
    adds r0, r1\n\
    ldrb r6, [r0, 0x8]\n\
    ldrh r7, [r0, 0xA]\n\
    ldrh r1, [r0, 0xC]\n\
    mov r12, r1\n\
    movs r2, 0xC\n\
    ldrsh r0, [r0, r2]\n\
    cmp r0, 0\n\
    beq _080F7CF8\n\
    ldr r2, =gUnknown_0203A034\n\
    ldr r0, [r2]\n\
    ldr r0, [r0]\n\
    lsls r1, r6, 1\n\
    adds r0, 0xC\n\
    adds r0, r1\n\
    movs r3, 0\n\
    ldrsh r0, [r0, r3]\n\
    adds r5, r1, 0\n\
    cmp r0, 0\n\
    bgt _080F7D10\n\
    b _080F7D0E\n\
    .pool\n\
_080F7CF8:\n\
    ldr r2, =gUnknown_0203A034\n\
    ldr r0, [r2]\n\
    ldr r0, [r0]\n\
    lsls r1, r6, 1\n\
    adds r0, 0xC\n\
    adds r0, r1\n\
    movs r3, 0\n\
    ldrsh r0, [r0, r3]\n\
    adds r5, r1, 0\n\
    cmp r0, 0x57\n\
    ble _080F7D10\n\
_080F7D0E:\n\
    movs r4, 0x1\n\
_080F7D10:\n\
    ldr r0, [r2]\n\
    ldr r0, [r0]\n\
    adds r0, 0xC\n\
    adds r2, r0, r5\n\
    ldrh r3, [r2]\n\
    movs r0, 0\n\
    ldrsh r1, [r2, r0]\n\
    lsls r0, r7, 16\n\
    asrs r0, 16\n\
    cmp r1, r0\n\
    bne _080F7D2A\n\
    movs r1, 0x1\n\
    mov r9, r1\n\
_080F7D2A:\n\
    mov r0, r9\n\
    cmp r0, 0\n\
    bne _080F7D4A\n\
    cmp r4, 0\n\
    beq _080F7D3C\n\
    strh r7, [r2]\n\
    b _080F7D4A\n\
    .pool\n\
_080F7D3C:\n\
    mov r1, r12\n\
    cmp r1, 0\n\
    beq _080F7D46\n\
    subs r0, r3, 0x1\n\
    b _080F7D48\n\
_080F7D46:\n\
    adds r0, r3, 0x1\n\
_080F7D48:\n\
    strh r0, [r2]\n\
_080F7D4A:\n\
    cmp r4, 0\n\
    bne _080F7DC4\n\
    mov r2, r9\n\
    cmp r2, 0\n\
    bne _080F7DCA\n\
    movs r2, 0\n\
_080F7D56:\n\
    ldr r0, =gUnknown_0203A034\n\
    ldr r0, [r0]\n\
    ldr r0, [r0]\n\
    adds r0, 0xC\n\
    adds r0, r5\n\
    movs r1, 0\n\
    ldrsh r3, [r0, r1]\n\
    adds r0, r2, 0x1\n\
    lsls r1, r0, 3\n\
    adds r4, r0, 0\n\
    cmp r3, r1\n\
    blt _080F7D78\n\
    movs r0, 0x8\n\
    b _080F7D94\n\
    .pool\n\
_080F7D78:\n\
    lsls r0, r2, 3\n\
    cmp r3, r0\n\
    blt _080F7D92\n\
    adds r0, r3, 0\n\
    cmp r3, 0\n\
    bge _080F7D86\n\
    adds r0, r3, 0x7\n\
_080F7D86:\n\
    asrs r0, 3\n\
    lsls r0, 3\n\
    subs r0, r3, r0\n\
    lsls r0, 24\n\
    lsrs r0, 24\n\
    b _080F7D94\n\
_080F7D92:\n\
    movs r0, 0\n\
_080F7D94:\n\
    cmp r0, 0x3\n\
    bhi _080F7DA0\n\
    ldr r3, =0x0000504c\n\
    b _080F7DA2\n\
    .pool\n\
_080F7DA0:\n\
    ldr r3, =0x00005057\n\
_080F7DA2:\n\
    adds r1, r0, r3\n\
    adds r2, 0x7\n\
    lsls r2, 24\n\
    lsrs r2, 24\n\
    adds r3, r5, r6\n\
    adds r3, 0x6\n\
    lsls r3, 24\n\
    movs r0, 0x1\n\
    str r0, [sp]\n\
    str r0, [sp, 0x4]\n\
    movs r0, 0x2\n\
    lsrs r3, 24\n\
    bl FillBgTilemapBufferRect_Palette0\n\
    adds r2, r4, 0\n\
    cmp r2, 0xA\n\
    ble _080F7D56\n\
_080F7DC4:\n\
    mov r0, r9\n\
    cmp r0, 0\n\
    beq _080F7DDC\n\
_080F7DCA:\n\
    ldr r0, =gUnknown_0203A034\n\
    ldr r0, [r0]\n\
    ldr r1, [r0]\n\
    ldrb r0, [r1, 0x14]\n\
    subs r0, 0x1\n\
    strb r0, [r1, 0x14]\n\
    mov r0, r8\n\
    bl DestroyTask\n\
_080F7DDC:\n\
    add sp, 0x8\n\
    pop {r3,r4}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .pool");
}
#endif // NONMATCHING

static void sub_80F7DF4(void)
{
    gUnknown_0203A034 = AllocZeroed(sizeof(*gUnknown_0203A034));
    gUnknown_0203A034->unk0 = AllocZeroed(sizeof(*gUnknown_0203A034->unk0));
    gUnknown_0203A034->unk4 = AllocZeroed(sizeof(*gUnknown_0203A034->unk4));
    gUnknown_0203A034->unk8 = AllocZeroed(BG_SCREEN_SIZE);
    gUnknown_0203A034->unkC[0] = AllocZeroed(BG_SCREEN_SIZE);
    gUnknown_0203A034->unkC[1] = AllocZeroed(BG_SCREEN_SIZE);
    gUnknown_0203A034->unkC[2] = AllocZeroed(BG_SCREEN_SIZE);
    gUnknown_0203A034->unkC[3] = AllocZeroed(BG_SCREEN_SIZE);
    gUnknown_0203A034->unk1C = AllocZeroed(0x1000);
    AllocateMonSpritesGfx();
}

static void sub_80F7E64(void)
{
    FREE_AND_SET_NULL(gUnknown_0203A034->unk0);
    FREE_AND_SET_NULL(gUnknown_0203A034->unk4);
    FREE_AND_SET_NULL(gUnknown_0203A034->unk8);
    FREE_AND_SET_NULL(gUnknown_0203A034->unkC[0]);
    FREE_AND_SET_NULL(gUnknown_0203A034->unkC[1]);
    FREE_AND_SET_NULL(gUnknown_0203A034->unkC[2]);
    FREE_AND_SET_NULL(gUnknown_0203A034->unkC[3]);
    FREE_AND_SET_NULL(gUnknown_0203A034->unk1C);
    FREE_AND_SET_NULL(gUnknown_0203A034);
    FreeMonSpritesGfx();
}

static void sub_80F7ED0(int windowId, u8 *str, int arg2)
{
    struct TextPrinterTemplate textPrinter;
    textPrinter.currentChar = str;
    textPrinter.windowId = windowId;
    textPrinter.fontId = 7;
    textPrinter.x = arg2;
    textPrinter.y = 2;
    textPrinter.currentX = arg2;
    textPrinter.currentY = 2;
    textPrinter.letterSpacing = 0;
    textPrinter.lineSpacing = 0;
    textPrinter.unk = 0;
    textPrinter.fgColor = 1;
    textPrinter.bgColor = 0;
    textPrinter.shadowColor = 8;
    AddTextPrinter(&textPrinter, 0, NULL);
    PutWindowTilemap(windowId);
}

void sub_80F7F30(void)
{
    u8 result = sub_80DAE0C(&gPlayerParty[gContestMonPartyIndex]);
    if (result)
    {
        sub_80DAB8C(gSpecialVar_ContestCategory, gSpecialVar_ContestRank);
        sub_80DB09C(gSpecialVar_ContestCategory);
    }

    gSpecialVar_Result = result;
}

u16 sub_80F7F7C(void)
{
    u16 result = 0;
    struct Pokemon *mon = &gPlayerParty[gContestMonPartyIndex];
    switch (gSpecialVar_ContestCategory)
    {
    case CONTEST_CATEGORY_COOL:
        if (GetMonData(mon, MON_DATA_COOL_RIBBON) > gSpecialVar_ContestRank)
            result = 1;
        break;
    case CONTEST_CATEGORY_BEAUTY:
        if (GetMonData(mon, MON_DATA_BEAUTY_RIBBON) > gSpecialVar_ContestRank)
            result = 1;
        break;
    case CONTEST_CATEGORY_CUTE:
        if (GetMonData(mon, MON_DATA_CUTE_RIBBON) > gSpecialVar_ContestRank)
            result = 1;
        break;
    case CONTEST_CATEGORY_SMART:
        if (GetMonData(mon, MON_DATA_SMART_RIBBON) > gSpecialVar_ContestRank)
            result = 1;
        break;
    case CONTEST_CATEGORY_TOUGH:
        if (GetMonData(mon, MON_DATA_TOUGH_RIBBON) > gSpecialVar_ContestRank)
            result = 1;
        break;
    }

    return result;
}

void sub_80F7FFC(void)
{
    u8 ribbonData;

    if (gContestFinalStandings[gContestPlayerMonIndex] != 0)
        return;

    switch (gSpecialVar_ContestCategory)
    {
    case CONTEST_CATEGORY_COOL:
        ribbonData = GetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_COOL_RIBBON);
        if (ribbonData <= gSpecialVar_ContestRank && ribbonData < 4)
        {
            ribbonData++;
            SetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_COOL_RIBBON, &ribbonData);
            if (GetRibbonCount(&gPlayerParty[gContestMonPartyIndex]) > 4)
                sub_80EE4DC(&gPlayerParty[gContestMonPartyIndex], MON_DATA_COOL_RIBBON);
        }
        break;
    case CONTEST_CATEGORY_BEAUTY:
        ribbonData = GetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_BEAUTY_RIBBON);
        if (ribbonData <= gSpecialVar_ContestRank && ribbonData < 4)
        {
            ribbonData++;
            SetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_BEAUTY_RIBBON, &ribbonData);
            if (GetRibbonCount(&gPlayerParty[gContestMonPartyIndex]) > 4)
                sub_80EE4DC(&gPlayerParty[gContestMonPartyIndex], MON_DATA_BEAUTY_RIBBON);
        }
        break;
    case CONTEST_CATEGORY_CUTE:
        ribbonData = GetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_CUTE_RIBBON);
        if (ribbonData <= gSpecialVar_ContestRank && ribbonData < 4)
        {
            ribbonData++;
            SetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_CUTE_RIBBON, &ribbonData);
            if (GetRibbonCount(&gPlayerParty[gContestMonPartyIndex]) > 4)
                sub_80EE4DC(&gPlayerParty[gContestMonPartyIndex], MON_DATA_CUTE_RIBBON);
        }
        break;
    case CONTEST_CATEGORY_SMART:
        ribbonData = GetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_SMART_RIBBON);
        if (ribbonData <= gSpecialVar_ContestRank && ribbonData < 4)
        {
            ribbonData++;
            SetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_SMART_RIBBON, &ribbonData);
            if (GetRibbonCount(&gPlayerParty[gContestMonPartyIndex]) > 4)
                sub_80EE4DC(&gPlayerParty[gContestMonPartyIndex], MON_DATA_SMART_RIBBON);
        }
        break;
    case CONTEST_CATEGORY_TOUGH:
        ribbonData = GetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_TOUGH_RIBBON);
        if (ribbonData <= gSpecialVar_ContestRank && ribbonData < 4)
        {
            ribbonData++;
            SetMonData(&gPlayerParty[gContestMonPartyIndex], MON_DATA_TOUGH_RIBBON, &ribbonData);
            if (GetRibbonCount(&gPlayerParty[gContestMonPartyIndex]) > 4)
                sub_80EE4DC(&gPlayerParty[gContestMonPartyIndex], MON_DATA_TOUGH_RIBBON);
        }
        break;
    }
}

void sub_80F8264(void)
{
    StringCopy(gStringVar1, gContestMons[gSpecialVar_0x8006].trainerName);
    sub_81DB5AC(gStringVar1);
}

void sub_80F8290(void)
{
    StringCopy(gStringVar3, gContestMons[gSpecialVar_0x8006].nickname);
}

void sub_80F82B4(void)
{
    u8 i;
    u8 count;

    for (i = 0, count = 0; i < 4; i++)
    {
        if (gContestMonConditions[gSpecialVar_0x8006] < gContestMonConditions[i])
            count++;
    }

    gSpecialVar_0x8004 = count;
}

void sub_80F82FC(void)
{
    gSpecialVar_0x8004 = gContestMonConditions[gSpecialVar_0x8006];
}

void sub_80F831C(void)
{
    u8 i;

    for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
        ;

    gSpecialVar_0x8005 = i;
}

void sub_80F834C(void)
{
    u8 i;

    for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
        ;

    StringCopy(gStringVar3, gContestMons[i].trainerName);
    sub_81DB5AC(gStringVar3);
}

void sub_80F8390(void)
{
    u8 i;

    for (i = 0; i < 4 && gContestFinalStandings[i] != 0; i++)
        ;

    StringCopy(gStringVar1, gContestMons[i].nickname);
}

void sub_80F83D0(void)
{
    SetMainCallback2(sub_80D7B24);
}

static void sub_80F83E0(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2(sub_80F83D0);
    }
}

void sub_80F840C(void)
{
    ScriptContext2_Enable();
    CreateTask(sub_80F83E0, 10);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
}

void sub_80F8438(void)
{
    gSpecialVar_0x8004 = gContestMons[gSpecialVar_0x8006].species;
}

static void sub_80F8458(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        SetMainCallback2(sub_80F5B00);
    }
}

void sub_80F8484(void)
{
    ScriptContext2_Enable();
    CreateTask(sub_80F8458, 10);
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
}

void sub_80F84B0(void)
{
    gSpecialVar_0x8004 = gContestPlayerMonIndex;
}

void sub_80F84C4(u8 taskId)
{
    u8 newTaskId;
    ScriptContext2_Enable();
    newTaskId = CreateTask(sub_80FC580, 0);
    SetTaskFuncWithFollowupFunc(newTaskId, sub_80FC580, sub_80F8508);
    gTasks[newTaskId].data[9] = taskId;
}

static void sub_80F8508(u8 taskId)
{
    if (gIsLinkContest & 0x4)
    {
        sub_80DA8C8(gContestMonPartyIndex);
        SetTaskFuncWithFollowupFunc(taskId, sub_80FC6BC, sub_80F8568);
    }
    else
    {
        sub_80DA8C8(gContestMonPartyIndex);
        gTasks[taskId].func = sub_81D9DE4;
    }
}

static void sub_80F8568(u8 taskId)
{
    SetTaskFuncWithFollowupFunc(taskId, sub_80FC804, sub_80F8584);
}

static void sub_80F8584(u8 taskId)
{
    SetTaskFuncWithFollowupFunc(taskId, sub_80FCE48, sub_80F85A0);
}

static void sub_80F85A0(u8 taskId)
{
    SetTaskFuncWithFollowupFunc(taskId, sub_80FC894, sub_80F85BC);
}

#ifdef NONMATCHING
static void sub_80F85BC(u8 taskId)
{
    u32 i;
    u8 sp0[4];
    u8 sp4[4];

    memset(sp0, 0, sizeof(sp0));
    memset(sp4, 0, sizeof(sp4));

    for (i = 0; i < gNumLinkContestPlayers; i++)
        sp0[i] = gTasks[taskId].data[i + 1];

    for (i = 0; i < gNumLinkContestPlayers; i++)
    {
        if (sp0[0] != sp0[i + 1])
            break;
    }

    if (i == gNumLinkContestPlayers)
        gSpecialVar_0x8004 = 0;
    else
        gSpecialVar_0x8004 = 1;

    for (i = 0; i < gNumLinkContestPlayers; i++)
        sp4[i] = gTasks[taskId].data[i + 5];
    
    gUnknown_02039F2B = sub_80F86E0(sp4);
    sub_80DB09C(gSpecialVar_ContestCategory);
    SetTaskFuncWithFollowupFunc(taskId, sub_80FCF40, sub_80F86B8);
}
#else
NAKED
static void sub_80F85BC(u8 taskId)
{
    asm_unified("\n\
    push {r4-r7,lr}\n\
    mov r7, r9\n\
    mov r6, r8\n\
    push {r6,r7}\n\
    sub sp, 0x8\n\
    lsls r0, 24\n\
    lsrs r6, r0, 24\n\
    movs r0, 0\n\
    str r0, [sp]\n\
    str r0, [sp, 0x4]\n\
    movs r3, 0\n\
    ldr r5, =gNumLinkContestPlayers\n\
    mov r12, r5\n\
    ldr r0, =gSpecialVar_0x8004\n\
    mov r9, r0\n\
    add r1, sp, 0x4\n\
    mov r8, r1\n\
    ldrb r0, [r5]\n\
    cmp r3, r0\n\
    bcs _080F8606\n\
    lsls r0, r6, 2\n\
    adds r0, r6\n\
    lsls r4, r0, 3\n\
    ldr r7, =gTasks + 0x8\n\
_080F85EC:\n\
    mov r1, sp\n\
    adds r2, r1, r3\n\
    adds r1, r3, 0x1\n\
    lsls r0, r1, 1\n\
    adds r0, r4\n\
    adds r0, r7\n\
    ldrh r0, [r0]\n\
    strb r0, [r2]\n\
    lsls r1, 24\n\
    lsrs r3, r1, 24\n\
    ldrb r0, [r5]\n\
    cmp r3, r0\n\
    bcc _080F85EC\n\
_080F8606:\n\
    movs r3, 0\n\
    mov r1, r12\n\
    ldrb r0, [r1]\n\
    cmp r3, r0\n\
    bcs _080F862A\n\
    adds r4, r0, 0\n\
    mov r2, sp\n\
_080F8614:\n\
    adds r0, r3, 0x1\n\
    lsls r0, 24\n\
    lsrs r3, r0, 24\n\
    cmp r3, r4\n\
    bcs _080F862A\n\
    mov r0, sp\n\
    adds r1, r0, r3\n\
    ldrb r0, [r2]\n\
    ldrb r1, [r1]\n\
    cmp r0, r1\n\
    beq _080F8614\n\
_080F862A:\n\
    mov r1, r12\n\
    ldrb r1, [r1]\n\
    cmp r3, r1\n\
    bne _080F8644\n\
    movs r0, 0\n\
    b _080F8646\n\
    .pool\n\
_080F8644:\n\
    movs r0, 0x1\n\
_080F8646:\n\
    mov r1, r9\n\
    strh r0, [r1]\n\
    movs r3, 0\n\
    mov r4, r12\n\
    ldrb r0, [r4]\n\
    cmp r3, r0\n\
    bcs _080F8678\n\
    mov r5, r8\n\
    lsls r0, r6, 2\n\
    adds r0, r6\n\
    lsls r2, r0, 3\n\
    ldr r7, =gTasks + 0x8\n\
_080F865E:\n\
    adds r1, r5, r3\n\
    adds r0, r3, 0x5\n\
    lsls r0, 1\n\
    adds r0, r2\n\
    adds r0, r7\n\
    ldrh r0, [r0]\n\
    strb r0, [r1]\n\
    adds r0, r3, 0x1\n\
    lsls r0, 24\n\
    lsrs r3, r0, 24\n\
    ldrb r1, [r4]\n\
    cmp r3, r1\n\
    bcc _080F865E\n\
_080F8678:\n\
    mov r0, r8\n\
    bl sub_80F86E0\n\
    ldr r1, =gUnknown_02039F2B\n\
    strb r0, [r1]\n\
    ldr r0, =gSpecialVar_ContestCategory\n\
    ldrb r0, [r0]\n\
    bl sub_80DB09C\n\
    ldr r1, =sub_80FCF40\n\
    ldr r2, =sub_80F86B8\n\
    adds r0, r6, 0\n\
    bl SetTaskFuncWithFollowupFunc\n\
    add sp, 0x8\n\
    pop {r3,r4}\n\
    mov r8, r3\n\
    mov r9, r4\n\
    pop {r4-r7}\n\
    pop {r0}\n\
    bx r0\n\
    .pool");
}
#endif // NONMATCHING

static void sub_80F86B8(u8 taskId)
{
    sub_80DCE58(0);
    SetTaskFuncWithFollowupFunc(taskId, sub_80FCFD0, sub_80F8714);
}

u8 sub_80F86E0(u8 *arg0)
{
    int i;
    u8 result = 0;

    for (i = 1; i < gNumLinkContestPlayers; i++)
    {
        if (arg0[result] < arg0[i])
            result = i;
    }

    return result;
}

void sub_80F8714(u8 taskId)
{
    int i;

    if (gSpecialVar_0x8004 == 1)
    {
        if (IsLinkTaskFinished())
            gTasks[taskId].func = sub_80F878C;
    }
    else
    {
        for (i = 0; i < 4; i++)
            StringGetEnd10(gContestMons[i].nickname);

        DestroyTask(taskId);
        SetDynamicWarp(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, -1);
        ScriptContext2_Disable();
        EnableBothScriptContexts();
    }
}

static void sub_80F878C(u8 taskId)
{
    sub_800AC34();
    gTasks[taskId].func = sub_80F87B4;
}

static void sub_80F87B4(u8 taskId)
{
    if (!gReceivedRemoteLinkPlayers)
    {
        DestroyTask(taskId);
        ScriptContext2_Disable();
        EnableBothScriptContexts();
    }
}
