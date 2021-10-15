#include "model.hxx"
#include <iostream>
#include <ge211.hxx>
#include <vector>

Model::Model()
{
    populate_En0(8);
    populate_En1(6);
    populate_En2(6, 3);
    add_wall(nmb_1st, nmb_1st_rows,0, wallie1);
    add_wall(nmb_1st, nmb_1st_rows,300, wallie2);
    add_wall(nmb_1st, nmb_1st_rows,600, wallie3);
    player_lives = 3;
    time_en.start_time();
    shoot_by_enemy(5);
    intensity_en0 = 3;
    intensity_en1 = 1;
    intensity_en2 = 2;
    aliens_killed = 0;
    int_over0 = 65;
    int_over1 = 32;
    int_over2 = 56;
}

void Model::move_player_left()
{
    if (playerpos.x > 0){
        playerpos.x -= 20;
    }

    //std::cout << "it worked!" << playerpos.x << "\n";
}

void Model::move_player_right()
{
    if (playerpos.x + playerdim.width < scene_dims.width){
        playerpos.x += 20;
    }
    //std::cout << "it worked!" << playerpos.x << "\n";
}

void
Model::populate_En0(int nmb)
{
    int top_margin = 20;
    int side_margin = 125;
    int spacing_width = 40;
    Position en0_pos(side_margin, top_margin);
    for (int i = 0; i < nmb; i++){
        En0.push_back(Block(en0_pos.x, en0_pos.y, en0.width, en0.height));
        en0_pos.x += en0.width + spacing_width;
    }
}

void
Model::populate_En1(int nmb)
{
    int top_margin = 88;
    int side_margin = 125;
    int spacing_width = 40;
    Position en1_pos(side_margin, top_margin);
    for (int i = 0; i < nmb; i++){
        En1.push_back(Block(en1_pos.x, en1_pos.y, en1.width, en1.height));
        en1_pos.x += en1.width + spacing_width;
    }
    en1_pos.x = side_margin + en1.width + (en1.width - spacing_width / 2);
    en1_pos.y += en1.height + 15;
    for (int i = 0; i < nmb; i++){
        En1.push_back(Block(en1_pos.x, en1_pos.y, en1.width, en1.height));
        en1_pos.x += en1.width + spacing_width;
    }
}

bool inRange(int low, int high, int x)
{
    return ((x-high)*(x-low) <= 0);
}

void Model::move_enemies(std::vector<Block> &enm,int& intensity)
{
    //std::cout << enm[enm.size()-1].x << "\n";
    if (inRange(scene_dims.width - 50, scene_dims.width + (50),enm[enm.size()
    -1].x ) && (intensity > 0)){
        intensity *= -1;
    }
    if (inRange( - 50, (50),enm[0].x ) && (intensity < 0))
    {
        intensity *= -1;
    }
    for (int i = 0; i < enm.size(); i++){
        enm[i].x += intensity;
    }
}
void
Model::populate_En2(int nmb, int rows)
{
    int top_margin = 185;
    int side_margin = 170;
    int spacing_width = 25;
    Position en2_pos(side_margin, top_margin);
    for (int j = 0; j < rows;  j++) {
        for (int i = 0; i < nmb; i++) {
            En2.push_back(Block(en2_pos.x, en2_pos.y, en2.width, en2.height));
            en2_pos.x += en2.width + spacing_width;
        }
        en2_pos.y += en2.height + 19;
        en2_pos.x = side_margin;
    }
}

void Model::shoot_by_enemy(int velocity){
    if (!rocket_launched_enemy){
        initialize_rocket_enemy();
    }
    if (gamemode == 0) {
        rocketpos_en.y += velocity;
    }
    if (gamemode == 1){
        rocketpos_en.y += velocity * (rand() % 15 - 2);
    }
    rocket_launched_enemy = true;
    //std::cou®t << "x pos is " << rocketpos.x << " and y pos is" << rocketpos
    // .y << "\n";
}

void Model::shoot(int velocity){
    if (!rocket_launched_player){
        initialize_rocket();
    }
    if (gamemode == 0) {
        rocketpos.y -= velocity;
    }
    if (gamemode == 1){
        rocketpos.y -= velocity * (rand() % 6 - 2);
    }
    rocket_launched_player = true;
    //std::cout << "x pos is " << rocketpos.x << " and y pos is" << rocketpos
    // .y << "\n";
}


void
Model::update(double dt)
{

    if (rocket_launched_player) {shoot(6);}
    if (rocketpos.y < 0){
        rocket_launched_player = false;
    }
    //std::cout << time_en.elapsed_time().seconds() << "\n" ;
    if (rocket_launched_enemy) {
        shoot_by_enemy(5);
    }
    if ((rocketpos_en.y > scene_dims.height) && time_en.elapsed_time() >
    (ge211::Duration( 5))){
        rocket_launched_enemy = false;
        time_en.reset();
        shoot_by_enemy(5);
    }
    if (!is_game_over()) {
        move_enemies(En0, intensity_en0);
        move_enemies(En1, intensity_en1);
        move_enemies(En2, intensity_en2);
    }

    if (collide_with_player()){
        reset_rocket_en();
        player_lives -= 1;
    }

    for (int i=0; i<En0.size(); i++){
        if (collide(En0[i])){
            En0[i] = En0.back();
            En0.pop_back();
            reset_rocket();
        }
    }

    for (int i=0; i<En1.size(); i++){
        if (collide(En1[i])){
            En1[i] = En1.back();
            En1.pop_back();
            reset_rocket();
        }
    }

    for (int i=0; i<En2.size(); i++){
        if (collide(En2[i])){
            En2[i] = En2.back();
            En2.pop_back();
            reset_rocket();
        }
    }


    for (int i=0; i<wallie1.size(); i++){
        if (collide_with_wall(wallie1[i], rocketpos, rocketdim)){
            wallie1[i] = wallie1.back();
            wallie1.pop_back();
            reset_rocket();
        } else if (collide_with_wall(wallie1[i], rocketpos_en, rocketdim_en)){
            wallie1[i] = wallie1.back();
            wallie1.pop_back();
            reset_rocket_en();
        }
    }
    for (int i=0; i<wallie2.size(); i++){
        if (collide_with_wall(wallie2[i], rocketpos, rocketdim)){
            wallie2[i] = wallie2.back();
            wallie2.pop_back();
            reset_rocket();
        } else if (collide_with_wall(wallie2[i], rocketpos_en, rocketdim_en)){
            wallie2[i] = wallie2.back();
            wallie2.pop_back();
            reset_rocket_en();
        }
    }

    for (int i=0; i<wallie3.size(); i++){
        if (collide_with_wall(wallie3[i], rocketpos, rocketdim)){
            wallie3[i] = wallie3.back();
            wallie3.pop_back();
            reset_rocket();
        } else if (collide_with_wall(wallie3[i], rocketpos_en, rocketdim_en)){
            wallie3[i] = wallie3.back();
            wallie3.pop_back();
            reset_rocket_en();
        }
    }
    if (is_game_over()){
        rocket_launched_enemy = false;
        rocket_launched_player = false;
        rocketpos.y = 0;
        rocketpos_en.y = scene_dims.height;
        move_enemies(En0, int_over0);
        move_enemies(En1, int_over1);
        move_enemies(En2, int_over2);
    }

}

void
Model::initialize_rocket()
{
    rocketpos.x = playerpos.x + playerdim.width/2;
    rocketpos.y = playerpos.y;
}

void
Model::initialize_rocket_enemy()
{
    std::vector<Block> big_vector;
    big_vector.reserve(En0.size() + En1.size() + En2.size());
    big_vector.insert(big_vector.end(), En0.begin(), En0.end());
    big_vector.insert(big_vector.end(), En1.begin(), En1.end());
    big_vector.insert(big_vector.end(), En2.begin(), En2.end());
    int rand_en = rand() % big_vector.size();
    rocketpos_en.x = big_vector[rand_en].x + big_vector[rand_en].width/2;
    rocketpos_en.y = big_vector[rand_en].y;
    //std::cout << big_vector.size() << " " << rand_en << "\n";
    //std::cout << rocketpos_en.x << " and my y is ; " << rocketpos_en.y;
}

bool Model::collide(Block enemy){
    int left_x = rocketpos.x;
    int top_y = rocketpos.y;
    int right_x = left_x + rocketdim.width;
    int bottom_y = top_y + rocketdim.height;
    if (right_x < enemy.x or left_x > (enemy.x + enemy.width)){
        return false;
    }
    if (bottom_y < enemy.y or top_y > (enemy.y + enemy.height)){
        return false;
    }
    aliens_killed++;
    //view.play_effect_invaderkilled()
    //std::cout << "Aliens killed: " << aliens_killed << "\n";
    return true;
}

bool Model::collide_with_player(){
    int left_x = rocketpos_en.x;
    int top_y = rocketpos_en.y;
    int right_x = left_x + rocketdim_en.width;
    int bottom_y = top_y + rocketdim_en.height;
    if (right_x < playerpos.x or left_x > (playerpos.x + playerdim.width)){
        return false;
    }
    if (bottom_y < playerpos.y or top_y > (playerpos.y + playerdim.height)){
        return false;
    }
    //std::cout << "it collided";
    return true;
}

bool Model::collide_with_wall(Block wallie, Position rocketp, Dimensions
rocketd)
{
    int left_x = rocketp.x;
    int top_y = rocketp.y;
    int right_x = left_x + rocketd.width;
    int bottom_y = top_y + rocketd.height;
    if (right_x < wallie.x or left_x > (wallie.x + wallie.width)) {
        return false;
    }
    if (bottom_y < wallie.y or top_y > (wallie.y + wallie.height)) {
        return false;
    }
    //std::cout << "it collided";
    return true;
}
void Model::reset_rocket()
{
    rocket_launched_player = false;
    rocketpos.y= -10;
}
void Model::reset_rocket_en()
{
    rocket_launched_enemy = false;
    rocketpos_en.y= scene_dims.height + 1 ;
}

bool
Model::is_game_over() const
{
    if (player_lives == 0){
        return true;
    }
    return false;
}

int
Model::lifes_left()
{
    return player_lives;
}


void Model::add_wall(int nmb, int rows, int side, std::vector<Block>& wallie)
{
    int top_margin = 540;
    int side_margin = 150 + side;
    int spacing = 0;
    Block wallie_block{side_margin, top_margin, 30,30};
    for (int j = 0; j < rows;  j++) {
        for (int i = 0; i < nmb; i++) {
            wallie.push_back(Block(wallie_block.x, wallie_block.y, wallie_block
            .width, wallie_block.height));
            wallie_block.x += wallie_block.width + spacing;
        }
        wallie_block.y += wallie_block.height + spacing;
        wallie_block.x = side_margin;
    }
}
