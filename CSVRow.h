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
    std::size_t size() const;
    std::vector<std::string> get_recipe_vector();
    std::string const& operator[](std::size_t index)const;       
    void getRecipes();        
    void write_recipe(std::vector<std::string> recipe_info);
    void readNextRow(std::istream& str);  
    std::vector<std::string> get_values_vector(int recipes_index);
    void edit_recipe(std::vector<std::string> recipe_info, int recipes_index);
    
    private:
    // std::map<std::string,std::vector<std::string> >   m_recipes_map;
    std::vector<std::string> m_recipes_vector;
    std::vector<std::string> m_line_vector;
    std::vector<std::vector<std::string>> m_values_vector;
};  
#endif /* CSVROW_H */
