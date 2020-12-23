#pragma once

/* #include "iGraphics.h" */
#include <stdio.h>
#include <string.h>
#include "GamePage.h"

typedef struct
{
    int stopwatch_end_min, stopwatch_end_sec;
    int win_score[15];
    int_tuple no_of_eggs[15];
} time_slot;

//time slot initialization
time_slot time_slot_arr[] = {{1, 0, {50, 90, 120, 180, 250}, {{25, 0, 0}, {25, 20, 0}, {30, 20, 10}, {20, 15, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 10}}},
                             {2, 0, {70, 100, 150, 220, 300}, {{25, 0, 0}, {25, 20, 0}, {20, 15, 10}, {20, 15, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 10}}},
                             {3, 0, {90, 120, 180, 250, 350}, {{25, 0, 0}, {25, 20, 0}, {20, 15, 10}, {20, 15, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 10}}}};

//placeholder initialization
placeholder placeholder_arr[] = {{AddVector(home_origin, {0, 2 * placeholder_grid}), {300, placeholder_height}, "PASSWORD", "Password should not cross 30 characters.", .page_no = SignUpPageNo},
                                 {AddVector(home_origin, {0, 3 * placeholder_grid}), {300, placeholder_height}, "LAST NAME", "Last name should not cross 30 characters.", .page_no = SignUpPageNo},
                                 {AddVector(home_origin, {0, 4 * placeholder_grid}), {300, placeholder_height}, "FIRST NAME", "First name should not cross 30 characters.", .page_no = SignUpPageNo},
                                 {AddVector(home_origin, {0, 5 * placeholder_grid}), {300, placeholder_height}, "USERNAME", "Username should not contain any commas and not cross 30 characters.", .page_no = SignUpPageNo},
                                 {AddVector(home_origin, {0, 3 * placeholder_grid}), {300, placeholder_height}, "PASSWORD", "Write your password.", .page_no = LoginInfoPageNo},
                                 {AddVector(home_origin, {0, 4 * placeholder_grid}), {300, placeholder_height}, "USERNAME", "Write your username.", .page_no = LoginInfoPageNo}};

int cnt = 0;

void HomePage()
{
    iShowBMP(0, 0, "images/blur_bg2.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 300, "images\\home_page_title.bmp");

    for (int i = 0; i < 7; i++)
    {
        if (i == 6 && !pause)
            continue;
        button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x) / 2;
        ButtonDraw(button_arr[i], red1);
    }
}

void ButtonDraw(button btn, rgb col)
{
    ChangeColor(col);
    iRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    if (btn.active)
        iFilledRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    double text_X = btn.origin.x + (btn.dimension.x - strlen(btn.str) * HEL_font_size) / 2;
    double text_Y = btn.origin.y + (btn.dimension.y - HEL_font_size) / 2;

    if (text_X < 0 || text_Y < 0)
    {
        printf("Too small Button.\n");
        return;
    }
    if (btn.active)
        ChangeColor(black);
    iText(text_X, text_Y, btn.str, GLUT_BITMAP_HELVETICA_18);
}

void LoginPage()
{

    iShowBMP(0, 0, "images/blur_bg3.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 400, "images\\catch_the_eggs_red.bmp");

    for (int i = 7; i < 9; i++)
    {
        button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x) / 2;
        ButtonDraw(button_arr[i], turquoise);
    }
}

void SignUp()
{
    iShowBMP(0, 0, "images/blur_bg4.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 200, "images\\create_profile_title.bmp");

    for (int i = 0; i < 4; i++)
    {
        placeholder_arr[i].origin.x = home_origin.x + (home_dimension.x - placeholder_arr[i].dimension.x) / 2;
        PlaceholderDraw(&placeholder_arr[i], turquoise);
    }

    button_arr[9].origin.x = home_origin.x + (home_dimension.x - 300) / 2;
    ButtonDraw(button_arr[9], turquoise);
    button_arr[25].origin.x = home_origin.x + home_dimension.x - (home_dimension.x - 300) / 2 - button_arr[25].dimension.x;
    ButtonDraw(button_arr[25], turquoise);
}

void PlaceholderDraw(placeholder *pl, rgb col)
{
    ChangeColor(col);

    iText(pl->origin.x, pl->origin.y + pl->dimension.y + 10, pl->title, GLUT_BITMAP_HELVETICA_18);
    iText(pl->origin.x, pl->origin.y - 15, pl->label, GLUT_BITMAP_HELVETICA_12);

    ChangeColor(white2);
    iFilledRectangle(pl->origin.x, pl->origin.y, pl->dimension.x, pl->dimension.y);

    ChangeColor(black);
    iText(pl->origin.x + 10, pl->origin.y + (pl->dimension.y - HEL_font_size) / 2, pl->input, GLUT_BITMAP_HELVETICA_18);
}

void AddProfileInfo()
{

    char username[50], first_name[50], last_name[50], password[50];

    for (int i = 0; i < 4; i++)
    {
        if (placeholder_arr[i].next_input > 30 || placeholder_arr[i].next_input == 0)
        {
            char temp[200] = "Number of characters should not exceed 30. Moreover, this info's can not empty.";
            strcpy(prompt_text, temp);
            popup_show = PopupNo;

            for (int i = 0; i < 4; i++)
            {
                int j;
                for (j = 0; j < strlen(placeholder_arr[i].input); j++)
                    placeholder_arr[i].input[j] = '\0';
                placeholder_arr[i].next_input = 0;
            }

            return;
        }
    }

    if (UsernameMatch(placeholder_arr[3].input) != -1)
    {
        char temp[200] = "This username is already taken. Try a new one.";
        strcpy(prompt_text, temp);
        popup_show = PopupNo;

        for (int i = 0; i < 4; i++)
        {
            int j;
            for (j = 0; j < strlen(placeholder_arr[i].input); j++)
                placeholder_arr[i].input[j] = '\0';
            placeholder_arr[i].next_input = 0;
        }

        return;
    }

    for (int i = 0; i < strlen(placeholder_arr[3].input); i++)
    {
        if (placeholder_arr[3].input[i] == ',' || placeholder_arr[3].input[i] == ' ')
        {
            char temp[200] = "Username and password should not contain commas or spaces.";
            strcpy(prompt_text, temp);
            popup_show = PopupNo;

            for (int i = 0; i < 4; i++)
            {
                int j;
                for (j = 0; j < strlen(placeholder_arr[i].input); j++)
                    placeholder_arr[i].input[j] = '\0';
                placeholder_arr[i].next_input = 0;
            }

            return;
        }
    }

    for (int i = 0; i < strlen(placeholder_arr[0].input); i++)
    {
        if (placeholder_arr[0].input[i] == ',' || placeholder_arr[3].input[i] == ' ')
        {
            char temp[200] = "Username and password should not contain commas or spaces.";
            strcpy(prompt_text, temp);
            popup_show = PopupNo;

            for (int i = 0; i < 4; i++)
            {
                int j;
                for (j = 0; j < strlen(placeholder_arr[i].input); j++)
                    placeholder_arr[i].input[j] = '\0';
                placeholder_arr[i].next_input = 0;
            }

            return;
        }
    }

    placeholder_arr[0].input[placeholder_arr[0].next_input++] = '\0';
    placeholder_arr[1].input[placeholder_arr[1].next_input++] = '\0';
    placeholder_arr[2].input[placeholder_arr[2].next_input++] = '\0';
    placeholder_arr[3].input[placeholder_arr[3].next_input++] = '\0';

    strcpy(username, placeholder_arr[3].input);
    strcpy(first_name, placeholder_arr[2].input);
    strcpy(last_name, placeholder_arr[1].input);
    strcpy(password, placeholder_arr[0].input);

    FILE *fp = NULL;
    if ((fp = fopen("profile.txt", "ab")) == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int str_sizes[] = {(int)strlen(username), (int)strlen(first_name), (int)strlen(last_name), (int)strlen(password)};

    if (fseek(fp, 0, SEEK_END))
    {
        printf("Error in random access.\n");
        return;
    }

    if (fwrite(str_sizes, sizeof(str_sizes), 1, fp) != 1)
    {
        printf("Error writing sizes.\n");
        return;
    }

    if (fwrite(username, str_sizes[0], 1, fp) != 1)
    {
        printf("Error writing username.\n");
        return;
    }

    if (fwrite(first_name, str_sizes[1], 1, fp) != 1)
    {
        printf("Error writing first name.\n");
        return;
    }

    if (fwrite(last_name, str_sizes[2], 1, fp) != 1)
    {
        printf("Error writing last name.\n");
        return;
    }

    if (fwrite(password, str_sizes[3], 1, fp) != 1)
    {
        printf("Error writing password.\n");
        return;
    }

    fclose(fp);

    page_no = HomePageNo;
}

void LoginInfo()
{
    iShowBMP(0, 0, "images/blur_bg1.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 300, "images\\catch_the_eggs_blue.bmp");

    for (int i = 4; i < 6; i++)
    {
        placeholder_arr[i].origin.x = home_origin.x + (home_dimension.x - placeholder_arr[i].dimension.x) / 2;
        PlaceholderDraw(&placeholder_arr[i], blue1);
    }

    button_arr[10].origin.x = home_origin.x + (home_dimension.x - button_arr[10].dimension.x) / 2;
    ButtonDraw(button_arr[10], blue1);
}

void GetProfileInfo()
{
    FILE *fp = NULL;

    if ((fp = fopen("profile.txt", "rb")) == NULL)
    {
        printf("Error opening the file in GetProfileInfo.\n");
        return;
    }

    int str_sizes[4];
    next_profile_data = 0;

    while (fread(str_sizes, sizeof(str_sizes), 1, fp) == 1)
    {
        char ret_username[str_sizes[0] + 1], ret_first_name[str_sizes[1] + 1], ret_last_name[str_sizes[2] + 1], ret_password[str_sizes[3] + 1];

        if (fread(ret_username, sizeof(ret_username) - 1, 1, fp) != 1)
        {
            printf("Error reading ret_username.\n");
            return;
        }

        ret_username[str_sizes[0]] = '\0';

        if (fread(ret_first_name, sizeof(ret_first_name) - 1, 1, fp) != 1)
        {
            printf("Error reading ret_first_name.\n");
            return;
        }

        ret_first_name[str_sizes[1]] = '\0';

        if (fread(ret_last_name, sizeof(ret_last_name) - 1, 1, fp) != 1)
        {
            printf("Error reading last_name.\n");
            return;
        }

        ret_last_name[str_sizes[2]] = '\0';

        if (fread(ret_password, sizeof(ret_password) - 1, 1, fp) != 1)
        {
            printf("Error reading password.\n");
            return;
        }

        ret_password[str_sizes[3]] = '\0';

        strcpy(profile_data[next_profile_data++], ret_username);
        strcpy(profile_data[next_profile_data++], ret_first_name);
        strcpy(profile_data[next_profile_data++], ret_last_name);
        strcpy(profile_data[next_profile_data++], ret_password);
    }

    fclose(fp);
}

int UsernameMatch(char *user_name)
{
    if (next_profile_data == -1)
        GetProfileInfo();
    int res = -1;

    for (int i = 0; i < next_profile_data; i += 4)
    {

        if (strcmp(profile_data[i], user_name))
            continue;
        res = i;
        break;
    }

    return res;
}

int PassMatch(char *pass)
{
    if (next_profile_data == -1)
        GetProfileInfo();
    int res = -1;

    for (int i = 3; i < next_profile_data; i += 4)
    {

        if (strcmp(profile_data[i], pass))
            continue;
        res = i;
        break;
    }

    return res;
}

void ProfileAccess()
{
    int res1 = UsernameMatch(placeholder_arr[5].input);
    if (res1 != -1 && !strcmp(placeholder_arr[4].input, profile_data[res1 + 3]))
    {
        loggedin_profile = res1;
        page_no = HomePageNo;

        char temp[100] = "Now you are logged in. Have fun!!! Press ok to continue.";
        strcpy(prompt_text, temp);
        popup_show = PopupNo;
    }
    else
    {
        //show invalid prompt
        char temp[200] = "Sorry, invalid username or password. Try to avoid spelling mistakes. Press ok to continue.";
        strcpy(prompt_text, temp);
        popup_show = PopupNo;
    }
}

void LevelPage()
{
    iShowBMP(0, 0, "images/blur_bg4.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    for (int i = 11; i < 16; i++)
    {
        button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x) / 2;
        ButtonDraw(button_arr[i], yellow1);
    }
}

void LevelOne()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;

    stopwatch_end_min = time_slot_arr[game_time_category].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[game_time_category].stopwatch_end_sec;

    win_score = time_slot_arr[game_time_category].win_score[0];
    flock_arr[0].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[0].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[0].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[0].three;

    strcpy(game_bg, "images\\a.bmp");
    page_no = GamePageNo;

    if (sound_is_on)
        PlaySound(NULL, NULL, 0);
    iResumeTimer(0);
    pause = 0;
}
void LevelTwo()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;

    stopwatch_end_min = time_slot_arr[game_time_category].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[game_time_category].stopwatch_end_sec;

    win_score = time_slot_arr[game_time_category].win_score[1];
    flock_arr[0].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[1].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[1].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[1].three;

    strcpy(game_bg, "images\\b.bmp");
    page_no = GamePageNo;

    if (sound_is_on)
        PlaySound(NULL, NULL, 0);

    iResumeTimer(0);
    pause = 0;
}
void LevelThree()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[0].golden.show = 1;

    stopwatch_end_min = time_slot_arr[game_time_category].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[game_time_category].stopwatch_end_sec;

    win_score = time_slot_arr[game_time_category].win_score[2];
    flock_arr[0].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[2].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[2].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[2].three;

    strcpy(game_bg, "images\\sp_bg.bmp");
    page_no = GamePageNo;

    if (sound_is_on)
        PlaySound(NULL, NULL, 0);

    iResumeTimer(0);
    pause = 0;
}
void LevelFour()
{
    flock_arr_size = 2;
    flock_arr[0].white.show = 1;
    flock_arr[1].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[1].blue.show = 1;

    stopwatch_end_min = time_slot_arr[game_time_category].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[game_time_category].stopwatch_end_sec;

    win_score = time_slot_arr[game_time_category].win_score[3];
    flock_arr[0].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[3].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[3].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[3].three;

    flock_arr[1].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[4].one;
    flock_arr[1].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[4].two;
    flock_arr[1].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[4].three;

    strcpy(game_bg, "images\\d.bmp");
    page_no = GamePageNo;

    if (sound_is_on)
        PlaySound(NULL, NULL, 0);

    iResumeTimer(0);
    pause = 0;
}
void LevelFive()
{
    flock_arr_size = 2;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[0].golden.show = 1;
    flock_arr[1].white.show = 1;
    flock_arr[1].blue.show = 1;
    flock_arr[1].golden.show = 1;

    stopwatch_end_min = time_slot_arr[game_time_category].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[game_time_category].stopwatch_end_sec;

    win_score = time_slot_arr[game_time_category].win_score[4];
    flock_arr[0].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[5].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[5].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[5].three;

    flock_arr[1].white.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[6].one;
    flock_arr[1].blue.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[6].two;
    flock_arr[1].golden.no_of_egg = time_slot_arr[game_time_category].no_of_eggs[6].three;

    strcpy(game_bg, "images\\a.bmp");
    page_no = GamePageNo;

    if (sound_is_on)
        PlaySound(NULL, NULL, 0);

    iResumeTimer(0);
    pause = 0;
}

void Intro()
{
    iShowBMP(0, 0, "images/main_bg.bmp");
}

void LoginPress()
{
    page_no = LoginInfoPageNo;
}

void SignupPress()
{
    page_no = SignUpPageNo;
}

void Prompt() //text should be lowercase otherwise the width needs to be adjusted.
{
    Vector origin = {375, 300}, dimension = {850, 300};
    int char_per_line = 40, vetical_padding = 10, side_padding = 40;
    int small_font = 9;
    /*     int lines = strlen(prompt_text)/char_per_line + (strlen(prompt_text)%char_per_line != 0);
    dimension.y = small_font*lines + vetical_padding*(lines-1) + side_padding*3 + button_height;
    dimension.x = side_padding*2 + small_font*char_per_line; */

    ChangeColor(light_yellow);
    iFilledRectangle(origin.x, origin.y, dimension.x, dimension.y);

    ChangeColor(black);
    iRectangle(origin.x + side_padding / 2, origin.y + side_padding / 2, dimension.x - side_padding, dimension.y - side_padding);

    /* Vector text_origin = {origin.x + side_padding, origin.y + dimension.y - side_padding - small_font}; */
    Vector text_origin = {origin.x + side_padding + (dimension.x - side_padding - strlen(prompt_text) * small_font) / 2, origin.y + dimension.y - 2 * side_padding};
    iText(text_origin.x, text_origin.y, prompt_text, GLUT_BITMAP_HELVETICA_18);

    ChangeColor(black);
    /*     for(int i = 0; i< lines; i++)
    {

        char temp[char_per_line+1];
        temp[char_per_line] = '\0';

        int lim = (i+1)*char_per_line;
        if(strlen(prompt_text) < lim)
        {
            lim = strlen(prompt_text);
            temp[lim - i*char_per_line ] = '\0';
        }

        for(int j = i*char_per_line, k = 0; j < lim; j++, k++)
            temp[k] = prompt_text[j];
        
        iText(text_origin.x, text_origin.y, temp, GLUT_BITMAP_HELVETICA_18);
        text_origin = SubVector(text_origin, {0, vetical_padding + small_font});
    } */

    button_arr[16].origin.x = origin.x + (dimension.x - button_arr[16].dimension.x) / 2;
    button_arr[16].origin.y = origin.y + side_padding;
    ButtonDraw(button_arr[16], red1);
}

void PromptPress()
{

    if (prompt_text[0] == 'G')
    {
        XPress();
    }

    popup_show = 0;
}

void LeaderboardDraw()
{
    if (top_nxt == 0)
        GetTopperInfo();

    iShowBMP(0, 0, "images/blur_bg1.bmp");
    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    if (game_time_category == 0)
        iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 120, "images\\s.bmp");
    if (game_time_category == 1)
        iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 120, "images\\m.bmp");

    if (game_time_category == 2)
        iShowBMP(home_origin.x, home_origin.y + home_dimension.y - 120, "images\\l.bmp");

    int vertical_padding = 50;
    Vector grid_one_origin = AddVector(home_origin, {0, home_dimension.y - 3 * vertical_padding});
    Vector grid_two_origin = AddVector(home_origin, {home_dimension.x / 3, home_dimension.y - 3 * vertical_padding});
    Vector grid_three_origin = AddVector(home_origin, {2 * home_dimension.x / 3, home_dimension.y - 3 * vertical_padding});

    if (game_time_category == 0)
        ChangeColor(red1);
    else if (game_time_category == 1)
        ChangeColor(grass_green);
    else if (game_time_category == 2)
        ChangeColor(blue1);

    iText(grid_one_origin.x + (home_dimension.x / 3 - 4 * HEL_font_size) / 2, grid_one_origin.y, "RANK", GLUT_BITMAP_HELVETICA_18);
    iLine(grid_one_origin.x + vertical_padding / 5, grid_one_origin.y - vertical_padding / 5, grid_one_origin.x + home_dimension.x / 3 - vertical_padding / 5, grid_one_origin.y - vertical_padding / 5);

    iText(grid_two_origin.x + (home_dimension.x / 3 - 8 * HEL_font_size) / 2, grid_two_origin.y, "USERNAME", GLUT_BITMAP_HELVETICA_18);
    iLine(grid_two_origin.x + vertical_padding / 5, grid_two_origin.y - vertical_padding / 5, grid_two_origin.x + home_dimension.x / 3 - vertical_padding / 5, grid_one_origin.y - vertical_padding / 5);

    iText(grid_three_origin.x + (home_dimension.x / 3 - 5 * HEL_font_size) / 2, grid_three_origin.y, "SCORE", GLUT_BITMAP_HELVETICA_18);
    iLine(grid_three_origin.x + vertical_padding / 5, grid_three_origin.y - vertical_padding / 5, grid_three_origin.x + home_dimension.x / 3 - vertical_padding / 5, grid_one_origin.y - vertical_padding / 5);

    if (game_time_category == 0)
        ChangeColor(turquoise);
    else if (game_time_category == 1)
        ChangeColor(white);
    else if (game_time_category == 2)
        ChangeColor(red1);

    for (int i = 0, rank = 1; i < top_nxt; i++)
    {
        if (i && top_scores[i - 1] != top_scores[i])
            rank++;

        grid_one_origin = SubVector(grid_one_origin, {0, vertical_padding});
        grid_two_origin = SubVector(grid_two_origin, {0, vertical_padding});
        grid_three_origin = SubVector(grid_three_origin, {0, vertical_padding});

        char str_rank[10], str_score[10];
        sprintf(str_rank, "%d", rank);
        sprintf(str_score, "%d", top_scores[i]);

        iText(grid_one_origin.x + (home_dimension.x / 3 - 2 * HEL_font_size) / 2, grid_one_origin.y, str_rank, GLUT_BITMAP_HELVETICA_18);
        iText(grid_two_origin.x + (home_dimension.x / 3 - 8 * HEL_font_size) / 2, grid_two_origin.y, toppers[i], GLUT_BITMAP_HELVETICA_18);
        iText(grid_three_origin.x + (home_dimension.x / 3 - strlen(str_score) * HEL_font_size) / 2, grid_three_origin.y, str_score, GLUT_BITMAP_HELVETICA_18);
    }

    button_arr[17].origin.x = home_origin.x + (home_dimension.x - button_arr[17].dimension.x) / 2;
    ButtonDraw(button_arr[17], blue1);
}

void BackPress1()
{
    page_no = HomePageNo;
}

void LeaderboardPress()
{
    page_no = LeaderboardPageNo;
}

void ExitPress()
{
    exit(0);
}

void StartPress()
{
    /* XPress(); */
    page_no = LevelPageNo;
}

void PausePress()
{
    iPauseTimer(0);
    pause = 1;
}

void ResumePress()
{
    iResumeTimer(0);
    pause = 0;
    page_no = GamePageNo;
}

void BackPress2()
{
    PausePress();
    page_no = HomePageNo;
}

void XPress()
{
    page_no = HomePageNo;
    iPauseTimer(0);
    pause = 0;
    Init = 1;
    floating_objects_size = 0;
    stopwatch_current_sec = stopwatch_current_min = 0;
    white_egg_cnt = blue_egg_cnt = golden_egg_cnt = poop_cnt = score = 0;

    for (int j = 0; j < flock_arr_size; j++)
    {
        flock_arr[j].golden.next_egg = 0;
        flock_arr[j].blue.next_egg = 0;
        flock_arr[j].white.next_egg = 0;

        flock_arr[j].golden.next_poop = 0;
        flock_arr[j].blue.next_poop = 0;
        flock_arr[j].white.next_poop = 0;
    }

    basket_size_next_perks = basket_speed_next_perks = extra_time_next_perks = 0;
    basket_no = 0;
    next_wind = 0;

    if (sound_is_on)
        PlaySound(TEXT("sounds\\twinkle.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void HelpPage()
{
    iShowBMP(0, 0, "images\\help.bmp");
    ButtonDraw(button_arr[22], blue1);
}

void HelpPress()
{
    page_no = HelpPageNo;
}

void SettingsPage()
{
    iShowBMP(0, 0, "images/blur_bg2.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    int padding = 50;
    iShowBMP(home_origin.x, home_origin.y + 12 * padding, "images\\settings_title.bmp");

    ChangeColor(yellow1);
    iText(home_origin.x + padding, home_origin.y + 11 * padding, "BACKGROUND SOUND:", GLUT_BITMAP_HELVETICA_18);

    ChangeColor(white);
    iFilledRectangle(home_origin.x + 2 * padding, home_origin.y + 10 * padding, 30, 30);
    iFilledRectangle(home_origin.x + home_dimension.x - 2 * padding - 30, home_origin.y + 10 * padding, 30, 30);

    ChangeColor(red1);
    iRectangle(home_origin.x + 2 * padding + 5, home_origin.y + 10 * padding + 5, 20, 20);
    iRectangle(home_origin.x + home_dimension.x - 2 * padding - 30 + 5, home_origin.y + 10 * padding + 5, 20, 20);

    if (sound_is_on)
        iFilledRectangle(home_origin.x + 2 * padding + 5, home_origin.y + 10 * padding + 5, 20, 20);
    else
        iFilledRectangle(home_origin.x + home_dimension.x - 2 * padding - 30 + 5, home_origin.y + 10 * padding + 5, 20, 20);

    ChangeColor(yellow1);
    iText(600, home_origin.y + 9 * padding, "ON", GLUT_BITMAP_HELVETICA_18);
    iText(915, home_origin.y + 9 * padding, "OFF", GLUT_BITMAP_HELVETICA_18);

    ChangeColor(yellow1);
    iText(home_origin.x + padding, home_origin.y + 8 * padding, "GAME DURATION:", GLUT_BITMAP_HELVETICA_18);

    ChangeColor(white);
    iFilledRectangle(home_origin.x + 70, home_origin.y + 7 * padding, 30, 30);
    iFilledRectangle(home_origin.x + 260, home_origin.y + 7 * padding, 30, 30);
    iFilledRectangle(home_origin.x + 450, home_origin.y + 7 * padding, 30, 30);

    ChangeColor(red1);
    iRectangle(home_origin.x + 70 + 5, home_origin.y + 7 * padding + 5, 20, 20);
    iRectangle(home_origin.x + 260 + 5, home_origin.y + 7 * padding + 5, 20, 20);
    iRectangle(home_origin.x + 450 + 5, home_origin.y + 7 * padding + 5, 20, 20);

    if (game_time_category == 0)
        iFilledRectangle(home_origin.x + 70 + 5, home_origin.y + 7 * padding + 5, 20, 20);
    else if (game_time_category == 1)
        iFilledRectangle(home_origin.x + 260 + 5, home_origin.y + 7 * padding + 5, 20, 20);
    else if (game_time_category == 2)
        iFilledRectangle(home_origin.x + 450 + 5, home_origin.y + 7 * padding + 5, 20, 20);

    iShowBMP(home_origin.x, home_origin.y + 5 * padding, "images\\time_des.bmp");

    button_arr[23].origin.x = home_origin.x + (home_dimension.x - button_arr[23].dimension.x) / 2;
    ButtonDraw(button_arr[23], yellow1);
}

void SettingsPress()
{
    page_no = SettingsPageNo;
}

void ProfilePress()
{
    page_no = ProfilePageNo;
}

void ProfilePage()
{
    iShowBMP(0, 0, "images/blur_bg2.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    iShowBMP(home_origin.x, home_origin.y + 600, "images\\profile_title.bmp");

    int vert_padding = 30;
    char user[300] = "USERNAME:  ";
    char first_name[300] = "FIRST:  ";
    char last_name[300] = "LAST:  ";
    char pass[300] = "PASSWORD: ";

    GetProfileInfo();

    if (loggedin_profile == -1)
        loggedin_profile = UsernameMatch(placeholder_arr[3].input);

    strcat(user, profile_data[loggedin_profile]);
    strcat(first_name, profile_data[loggedin_profile + 1]);
    strcat(last_name, profile_data[loggedin_profile + 2]);
    strcat(pass, profile_data[loggedin_profile + 3]);

    ChangeColor(blue1);
    iText(home_origin.x + 2 * vert_padding, home_origin.y + 16 * vert_padding, user, GLUT_BITMAP_HELVETICA_18);
    iText(home_origin.x + 2 * vert_padding, home_origin.y + 14 * vert_padding, first_name, GLUT_BITMAP_HELVETICA_18);
    iText(home_origin.x + 2 * vert_padding, home_origin.y + 12 * vert_padding, last_name, GLUT_BITMAP_HELVETICA_18);
    iText(home_origin.x + 2 * vert_padding, home_origin.y + 10 * vert_padding, pass, GLUT_BITMAP_HELVETICA_18);

    button_arr[24].origin.x = home_origin.x + (home_dimension.x - button_arr[24].dimension.x) / 2;
    ButtonDraw(button_arr[24], blue1);
}

void CancelPress()
{
    page_no = LoginPageNo;
}