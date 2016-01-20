/******************************************************************************
/* @file Contains common elements, constants and typedefs of the DBSCAN module.
/*
/*
/* @author langenhagen
/* @version 150511
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <limits>
#include <set>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

namespace DBSCAN {

    /// typedef for abstracting single/double precision.
    typedef float real;
    
    /// "noise" cluster id for points that belong to noise.
    const unsigned int NOISE = 0;

    /// The DataPoint class.
    class DataPoint;
   
    /// Set of data point vectors.
    typedef std::set<DataPoint*> DataPointSet;

    /// A vector of Pointers to DataPoints.
    typedef std::vector<DataPoint*> DataPointVector;

} // END namespace DBSCAN