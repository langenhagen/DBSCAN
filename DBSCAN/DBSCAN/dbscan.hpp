/******************************************************************************
/* @file Implements the DBSCAN algorithm.
/*
/*
/* @author langenhagen
/* @version 1500508
/******************************************************************************/
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers

#include "DataPoint.hpp"

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)

#include <algorithm> // nth_element

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


/// The namespace of the DBSCAN module.
namespace DBSCAN {

    unsigned int dbscan( std::vector<DataPoint>& db, real eps, unsigned int min_pts);
    void expand_cluster( DataPointSet& N_p, const unsigned int C, const real eps, const unsigned int min_pts, std::vector<DataPoint>& db);
    DataPointSet get_neighbors( const DataPoint* p, const real eps, std::vector<DataPoint>& db);
    real squared_distance( const DataPoint* a, const DataPoint* b);


    /** Performs the classic DBSCAN algorithm.
     * @param db All data points that are to be considered by the algorithm.
     * @param eps The epsilon representing the radius of the epsilon-neighborhood.
     * @param min_pts The minimum number of points to be found within an epsilon-neigborhood.
     * @return The number of clusters that are retrieved by the algorithm.
     */
    unsigned int dbscan( std::vector<DataPoint>& db, const real eps, const unsigned int min_pts) {
        assert( eps >= 0 && "eps must not be negative");
        assert( min_pts > 0 && "min_pts must be greater than 0");
        unsigned int C(0);

        for( auto p_it = db.begin(); p_it != db.end(); ++p_it) {
            DataPoint* p = &*p_it;

            if( p->is_processed())
                continue;

            DataPointSet N_p = get_neighbors( p, eps, db);

            if( N_p.size() < min_pts)
                p->cluster(DBSCAN::NOISE);
            else {
                ++C;
                p->cluster( C);
                expand_cluster( N_p, C, eps, min_pts, db);
            }
        }
        return C;
    }


    /** Expands a given cluster.
     * @param N_p The neighborhood of some point already belonging to the given cluster.
     * @param C the cluster number.
     * @param eps The epsilon representing the radius of the epsilon-neighborhood.
     * @param min_pts The minimum number of points to be found within an epsilon-neigborhood.
     * @param db All data points that are to be considered by the algorithm.
     */
    void expand_cluster( DataPointSet& N_p, const unsigned int C, const real eps, const unsigned int min_pts, std::vector<DataPoint>& db) {

        for( auto q_it = N_p.begin(); q_it!=N_p.end(); ++q_it) {
            DataPoint* q = *q_it;

            if( q->cluster() == DBSCAN::NOISE)
                q->cluster( C);

            if( q->is_processed())
                continue;

            q->processed(true);

            DataPointSet N_q = get_neighbors( q, eps, db);
            if( N_q.size() >= min_pts) {
                N_p.insert( N_q.begin(), N_q.end());
            }
        }
    }


    /** Retrieves all points in the epsilon-surrounding of the given data point, including the point itself.
     * @param p The datapoint which represents the center of the epsilon surrounding.
     * @param eps The epsilon value that represents the radius for the neigborhood search.
     * @param db The database consisting of all datapoints that are checked for neighborhood.
     * @param A set of pointers to datapoints that lie within the epsilon-neighborhood 
     *        of the given point p, including p itself.
     */
    DataPointSet get_neighbors( const DataPoint* p, const real eps, std::vector<DataPoint>& db) {
        assert( eps >= 0 && "eps must not be negative");
        DataPointSet ret;

        const real eps_sq = eps*eps;

        for( auto q_it=db.begin(); q_it!=db.end(); ++q_it) {
            DataPoint* q = &*q_it;
            if( squared_distance( p, q) <= eps_sq) {
                ret.insert( q);
            }
        }
        return ret;
    }


    /** Retrieves the squared euclidean distance of two DataPoints.
     * @param a The first DataPoint.
     * @param b The second DataPoint. Both data points must have the same dimensionality.
     */
    real squared_distance( const DataPoint* a, const DataPoint* b) {
        const std::vector<real>& a_data = a->data();
        const std::vector<real>& b_data = b->data();
        const unsigned int vec_size = a_data.size();
        assert( vec_size == b_data.size() && "Data-vectors of both DataPoints must have same dimensionality");
        real ret(0);

        for( unsigned int i=0; i<vec_size; ++i) {
            ret += std::pow( a_data[i]-b_data[i], 2);
        }
        return ret;
    }

} // ENS namespace DBSCAN