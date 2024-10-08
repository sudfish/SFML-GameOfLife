#include "models/Cell.hpp"
#include "DEFINITIONS.hpp"

namespace GameOfLife {
    Cell::Cell(int row, int column, CellState state)
        : row(row), column(column), state(state)
    {
        this->drawableCell.setSize(sf::Vector2f(CELL_WIDTH, CELL_HEIGHT));
        this->drawableCell.setOutlineThickness(CELL_OUTLINE_THICKNESS);
        this->drawableCell.setOutlineColor(CELL_OUTLINE_COLOR);
        this->UpdateColor(false, false);
    }

    void Cell::SetCellState(CellState state){
        this->state = state;
    }

    bool Cell::IsAlive(){
        return this->state==ALIVE || this->state==ALIVE_TO_DEAD;
    }

    bool Cell::WillDie(){
        return this->state==DEAD || this->state==ALIVE_TO_DEAD;
    }

    bool Cell::WillLive(){
        return this->state==ALIVE || this->state==DEAD_TO_ALIVE;
    }

    sf::RectangleShape &Cell::GetDrawableCell(){
        return this->drawableCell;
    }

    void Cell::Update(bool randomColors, bool trailColors){
        this->UpdateState();
        this->UpdateColor(randomColors, trailColors);
    }

    void Cell::UpdateState(){
        if(this->state == ALIVE || this->state == DEAD_TO_ALIVE){
            this->state = ALIVE;
            this->deadShade = 0;
        } 
        else{
            this->state = DEAD;
            if(this->deadShade < sizeof(this->shades)-1) this->deadShade++;
        } 
    }

    void Cell::UpdateColor(bool randomColors, bool trailColors){
        if(this->state == ALIVE){
            if(randomColors) this->drawableCell.setFillColor(this->GetRandomColor());
            else this->drawableCell.setFillColor(CELL_ALIVE_FILL_COLOR);
        } else if (this->state == DEAD){
            if(trailColors) this->drawableCell.setFillColor(this->shades[this->deadShade]);
            else this->drawableCell.setFillColor(CELL_DEAD_FILL_COLOR);
        }
    }

    sf::Color Cell::GetRandomColor(){
        int randomIndex = std::rand() % (sizeof(this->colors) / sizeof(this->colors[0]));
        return this->colors[randomIndex];
    }
}
