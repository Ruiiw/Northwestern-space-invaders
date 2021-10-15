#pragma once

#include "model.hxx"
#include <iostream>

class View
{
public:
    explicit View(Model const&, ge211::Mixer&);
    View(int model);
    ge211::Dims<int> initial_window_dimensions() const;
    void draw(ge211::Sprite_set& set);
    Model const& model_;
    void load_audio_();
    void play_effect_shoot() const;
    void play_effect_invaderkilled() const;

private:
    //ge211::Rectangle_sprite const player_sprite;
    //ge211::Rectangle_sprite const en1_sprite;
    //ge211::Rectangle_sprite const en2_sprite;
    ge211::Rectangle_sprite firstwall_sprite;
    ge211::Rectangle_sprite const shoot_player_sprite;
    ge211::Rectangle_sprite const shoot_enemy_sprite;
    //ge211::Text_sprite const lifes_player_sprite;
    ge211::Image_sprite const morty_pic;
    ge211::Image_sprite const loyola_pic;
    ge211::Image_sprite const uchi_pic;
    ge211::Image_sprite const uiuc_pic;
    ge211::Mixer& mixer_;
    ge211::Sound_effect invaderkilled_sound_;
    ge211::Sound_effect shoot_sound_;

};
