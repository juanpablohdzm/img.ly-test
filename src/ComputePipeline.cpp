//
// Created by juanp on 4/16/2025.
//

#include "ComputePipeline.h"

#include <iostream>

#include "actions/Load/LoadFactory.h"

ActionResult ComputePipeline::execute(const std::string& uri){

    ActionResult result;
    ActionResult previous{
        uri,
        "file"
    };
    if (!LoadFactory::execute(std::move(previous), result))
    {
        std::cout << "Failed to execute action data from uri: " << uri << std::endl;
    }

    return result;
}
