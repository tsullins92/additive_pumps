/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSVRow.h
 * Author: tim
 *
 * Created on July 6, 2017, 3:20 PM
 */

#ifndef CSVROW_H
#define CSVROW_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

class CSVRow
{
    public:
        
        std::size_t size() const
        {
            return m_recipes_map.size();
        }

        
        std::vector<std::string>& operator[](std::string key)
        {
            return m_recipes_map[key];
        }
        
        void getRecipes()
        {   
        
            std::string                 cell;
            std::string                 line;
            std::vector<std::string>    line_vector;
            std::string                 recipes_key;
            std::ifstream               input_file("recipes.csv");
            std::stringstream           line_stream;
            
            while(std::getline(input_file, line, '\n'))
            {
                line_stream << line;
                while(std::getline(line_stream, cell, ','))
                {
                    line_vector.push_back(cell);
                }
                recipes_key = line_vector[0];
                line_vector.erase(line_vector.begin());
                m_recipes_map[recipes_key] = line_vector;
            }
        }
        
        
    private:
        std::map<std::string,std::vector<std::string>>   m_recipes_map;
        
};
#endif /* CSVROW_H */

