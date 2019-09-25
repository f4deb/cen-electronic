/*
 * $Id$
 * Ce fichier est confidentiel. Il est la propri�t� de :
 * Oalia SA
 * 38 Boulevard Henri Sellier
 * 92150 Suresnes, France
 * Tous droits r�serv�s.
 */
package com.cen.pic30f.common.math;

/**
 * Encapsulate notion of point which is a struct in C version.
 */
public class Point {

    public float x;

    public float y;

    public Point() {

    }

    public Point(float x, float y) {
        this.x = x;
        this.y = y;
    }
}
