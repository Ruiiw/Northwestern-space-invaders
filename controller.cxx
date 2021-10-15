#include "controller.hxx"
#include "model.hxx"
#include <iostream>


Controller::Controller(Model& model)
        : model_(model),
          view_(model_, mixer())
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}
ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::left()) {
        model_.move_player_left();

    }
    if (key == ge211::Key::right()) {
        model_.move_player_right();
    }
    if (key == ge211::Key::code(' ')) {
        model_.shoot(1);
        view_.play_effect_shoot();
    }
}

void
Controller::on_frame(double dt)
{
    model_.update(dt);
}
