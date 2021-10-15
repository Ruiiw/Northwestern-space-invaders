#include "view.hxx"
typedef ge211::Color color;
static color const player_color{255, 255, 127};
static color const en1_color{234, 255, 127};
static color const en2_color{133, 24, 86};
static color const rocket_player_color{255, 0, 86};
static color const rocket_enemy_color{0, 255, 0};
static color const firstwall_color{0, 255, 0};
static std::string const shoot_effect_filename {"shoot.wav"};
static std::string const invaderkilled_effect_filename {"invaderkilled.wav"};
//ge211::Font sans30{"./sans.ttf", 30};


View::View(Model const& model, ge211::Mixer& mixer)
        : model_(model),
          //player_sprite(model.playerdim, player_color),
          //en1_sprite(model.en1 , en1_color),
          //en2_sprite(model.en2 , en2_color),
          shoot_player_sprite(model.rocketdim , rocket_player_color),
          shoot_enemy_sprite(model.rocketdim_en , rocket_enemy_color),
          morty_pic("Unknown.png"),
          loyola_pic("loyola.png"),
          uchi_pic("UChi.png"),
          uiuc_pic("UIUC.jpg"),
          firstwall_sprite({30,30}, firstwall_color),
          mixer_(mixer)
          //lifes_player_sprite("Hello this is a try" , sans30)
{
    if (mixer_.is_enabled()) {
        load_audio_();
    }
}

ge211::Dims<int>
View::initial_window_dimensions() const
{
    return scene_dims;
}

void
View::draw(ge211::Sprite_set& set)
{
    set.add_sprite(morty_pic, model_.playerpos);
    //set.add_sprite(player_sprite, model_.playerpos);
    for (int i = 0; i<model_.En0.size(); i++){
        set.add_sprite(loyola_pic, model_.En0[i].top_left());
    }
    for (int i = 0; i<model_.En1.size(); i++){
        set.add_sprite(uchi_pic, model_.En1[i].top_left());
    }
    for (int i = 0; i<model_.En2.size(); i++){
        set.add_sprite(uiuc_pic, model_.En2[i].top_left());
    }

    for (int i = 0; i<model_.wallie1.size(); i++){
        if(model_.is_game_over()) {
            color firstwall_color
                    {static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255)};
            firstwall_sprite.recolor(firstwall_color);
        }
        set.add_sprite(firstwall_sprite, model_.wallie1[i].top_left());
    }
    for (int i = 0; i<model_.wallie2.size(); i++){
        if(model_.is_game_over()) {
            color firstwall_color
                    {static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255)};
            firstwall_sprite.recolor(firstwall_color);
        }
        set.add_sprite(firstwall_sprite, model_.wallie2[i].top_left());
    }
    for (int i = 0; i<model_.wallie3.size(); i++){
        if(model_.is_game_over()) {
            color firstwall_color
                    {static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255),
                     static_cast<uint8_t>(rand() % 255)};
            firstwall_sprite.recolor(firstwall_color);
        }
        set.add_sprite(firstwall_sprite, model_.wallie3[i].top_left());
    }
    if (model_.rocket_launched_player){
        set.add_sprite(shoot_player_sprite, {model_.rocketpos.x, model_
        .rocketpos.y});
    }
    if (model_.rocket_launched_enemy){
        set.add_sprite(shoot_enemy_sprite, {model_.rocketpos_en.x, model_
        .rocketpos_en.y});
    }
    //set.add_sprite(lifes_player_sprite, {0,740});
    //std::cout << "draw szn!" << model_.playerpos.x << "\n";
}

void
View::play_effect_shoot() const
{
    mixer_.try_play_effect(shoot_sound_);
}

void
View::play_effect_invaderkilled() const
{
    mixer_.try_play_effect(invaderkilled_sound_);
}


void
View::load_audio_()
{
    shoot_sound_.try_load(shoot_effect_filename, mixer_);
    invaderkilled_sound_.try_load(invaderkilled_effect_filename, mixer_);
}
