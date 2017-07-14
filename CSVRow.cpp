/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CSVRow.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   

std::string const& CSVRow::operator[](std::size_t index) const
{
    return m_line_vector[index];
}

std::size_t CSVRow::size() const
{
    return m_line_vector.size();
}
        
std::vector<std::string> CSVRow::get_vector()
{
    return m_recipes_vector;
}
            

void CSVRow::readNextRow(std::istream& str)
{
    std::string         line;
    std::getline(str, line);

    std::stringstream   lineStream(line);
    std::string         cell;

    m_line_vector.clear();
    while(std::getline(lineStream, cell, ','))
    {
        m_line_vector.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        m_line_vector.push_back("");
    }
}

void CSVRow::getRecipes()
{   
std::ifstream       file("recipes.csv");
CSVRow              row;
    while(file >> row)
    {
        m_recipes_vector.push_back(row[0]);
    }
}

void CSVRow::write_recipe(std::vector<std::string> recipe_info)
{
    std::ofstream               output_file;
    output_file.open("recipes.csv", std::ios_base::app);    //open file in append mode
    output_file << "\n";
    for (int i=0;i<recipe_info.size();++i)
    {
        char value_check = recipe_info[i][0];
        if(!isalpha(value_check))                           //make sure that we are only writing numerical values to recipes.csv
        {
            output_file << recipe_info[i];
            if(i<(recipe_info.size()-1))   
            {
                output_file << ",";
            }
        }
    }               
}