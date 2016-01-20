/******************************************************************************
/* @file Contains the DataPoint class that represents multi-dimensional points.
/*
/*
/* @author langenhagen
/* @version 150508
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers

#include "common.hpp"

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <assert.h>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS

namespace DBSCAN {

    /** Implements multi-dimensional numeric points.
     */
    class DataPoint {

    private: // vars

        std::vector<real> _data;    ///< The data elements.
        unsigned int _cluster;      ///< The cluster ID. 0 meams noise.
        bool _is_processed;         ///< A flag indicating if the object is already processed.
    
    public: // ctor & dtor

        /** Main constructor.
         * Sets the cluster membership to "noise" (DBSCAN::NOISE) and sets the processed-flag to false.
         */
        DataPoint() : _data( std::vector<real>()), _cluster(DBSCAN::NOISE), _is_processed( false) 
        {}

        //
        // Copy construction done by the compiler generated copy constructor.
        //

        /// Destructor.
        ~DataPoint() 
        {}

    public: // methods
    
        /** Retrieves a reference to the data vector.
         * @return A reference to the data vector that stores the data elements.
         */
        inline std::vector<real>& data() { return _data; }

        /** Retrieves a const reference to a data vector.
         * Constant method.
         * @return A const reference to the data vector that stores the data elements.
         */
        inline const std::vector<real>& data() const { return _data; }


        /** Sets the cluster to a given value.
         * @param i The cluster number. DBSCAN::NOISE means noise by convention.
         */
        inline void cluster( unsigned int i) { _cluster = i; }

        /** Returns the cluster number. DBSCAN::NOISE means noise by convention.
         * @return The cluster number. DBSCAN::NOISE means noise by convention.
         */
        inline const unsigned int cluster() const { return _cluster; }

        /** Sets the processed flag.
         * @param b The new processed flag.
         */
        inline void processed( bool b) { _is_processed = b; }
    
        /** Retrieves the processed flag.
         * @return Returns either TRUE or FALSE.
         */
        inline bool is_processed() const { return _is_processed; }
    
        /** Retrieves the noise flag.
         * @return Returns either TRUE or FALSE.
         */
        inline bool is_noise() const { return _cluster == DBSCAN::NOISE; }

    public: // operators

        /** An index operator that retrieves the idx-th element from the data vector.
         * @param idx The index pointing to the position of the data element to retrieve. Must be within the range of the data-vectors dimensionality.
         * @return Returns the element at the idx-th position of the DataPoint.
         * @see data()
         */
        inline real operator[]( const std::size_t idx) const { 
            assert( _data.size()>idx && "Index must be within _data's range.");
            return _data[idx];
        }

    };

} // END namespace DBSCAN