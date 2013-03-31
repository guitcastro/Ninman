/*
 * File:   NinmanGameGraph.h
 * Author: guilherme
 *
 * Created on 28 de Novembro de 2011, 21:15
 */

#ifndef NINMANGAMEGRAPH_H
#define	NINMANGAMEGRAPH_H

#include "allegro.h"
#include "Ninman.h"
#include "Ghost.h"
#include "NinmanConfig.h"
#include <string>

class NinmanGameGraph {
public:
    NinmanGameGraph();
    NinmanGameGraph(const NinmanGameGraph& orig);
    virtual ~NinmanGameGraph();
    static int DrawGameOptions ();
    static void drawInitGame();
private:
    static void DrawOptions(int y);
};

#endif	/* NINMANGAMEGRAPH_H */

