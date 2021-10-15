#pragma once

#include "model.hxx"
#include "view.hxx"
#include <iostream>
#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller(Model&);

    ge211::Dims<int> initial_window_dimensions() const override;
    void on_key(ge211::Key) override;
    void on_frame(double dt) override;
protected:
    void draw(ge211::Sprite_set& set) override;

private:

    /// Private data members
    Model model_;
    View view_;
};
