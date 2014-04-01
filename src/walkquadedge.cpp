#include "walkquadedge.h"

#include "vertex.h"
#include "edge.h"
#include "cell.h"

#include <cassert>
#include <iostream>
#include <string>

// Copied from StackOverFlow, originally from Herb Sutter's GotW#29
// This code results in ci_string being a case insensitive (for latin letters)
// string class.
struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char c1, char c2) { return toupper(c1) == toupper(c2); }
    static bool ne(char c1, char c2) { return toupper(c1) != toupper(c2); }
    static bool lt(char c1, char c2) { return toupper(c1) <  toupper(c2); }
    static int compare(const char* s1, const char* s2, size_t n) {
        while( n-- != 0 ) {
            if( toupper(*s1) < toupper(*s2) ) return -1;
            if( toupper(*s1) > toupper(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a) {
        while( n-- > 0 && toupper(*s) != toupper(a) ) {
            ++s;
        }
        // modification suggested in comments on:
        // http://stackoverflow.com/questions/11635/case-insensitive-string-comparison-in-c
        return n >= 0 ? s : NULL;
    }
};

typedef std::basic_string<char, ci_char_traits> ci_string;
// End copied code

WalkQuadEdge::WalkQuadEdge(Cell *cell)
{
    CellVertexIterator itr(cell);
    Vertex *v = itr.next();
    assert(v != NULL);
    currentEdge = v->getEdge();
}

WalkQuadEdge::WalkQuadEdge(Edge *startingPoint)
    : currentEdge(startingPoint) {}

static inline void printHelp(std::ostream &out) {
    out << "Interactive WalkQuadEdge commands: " << std::endl;
    out << "go <direction> -- sets the current edge to the edge in that direction" << std::endl;
    out << "\t" << "<direction> can be one of:" << std::endl;
    out << "\t" << "sym, onext, oprev, rnext, rprev, lnext, lprev, dnext, dprev" << std::endl;
    out << "print <what> -- prints the given edge" << std::endl;
    out << "\t" << "<what> can be one of:" << std::endl;
    out << "\t" << "current - prints the current edge's origin" << std::endl <<
           "\t\t" << " and destination and the face ids for each side" << std::endl;
    out << "\t" << "left, right - prints the edges around the face on that side" << std::endl;
    out << "quit -- exits the interactive quad-edge walk" << std::endl;
}

static inline Edge *readAndGetNextEdge(std::istream &in, std::ostream &out,
                                       Edge *currentEdge) {
    std::string tmp;
    in >> tmp;
    ci_string next(tmp.c_str());
    if (next == ci_string("sym")) {
        return currentEdge->Sym();
    } else if (next == ci_string("onext")) {
        return currentEdge->Onext();
    } else if (next == ci_string("oprev")) {
        return currentEdge->Oprev();
    } else if (next == ci_string("rnext")) {
        return currentEdge->Rnext();
    } else if (next == ci_string("rprev")) {
        return currentEdge->Rprev();
    } else if (next == ci_string("lnext")) {
        return currentEdge->Lnext();
    } else if (next == ci_string("lprev")) {
        return currentEdge->Lprev();
    } else if (next == ci_string("dnext")) {
        return currentEdge->Dnext();
    } else if (next == ci_string("dprev")) {
        return currentEdge->Dprev();
    } else {
        out << "Unknown direction.  Current edge did not change." << std::endl;
        return currentEdge;
    }
}

static inline void printEdge(std::ostream &out, Edge *e) {
    out << "Edge " << e->getID() << " from " << e->Org()->pos << " to " <<
           e->Dest()->pos << "." << std::endl << "  Left face: " <<
           e->Left()->getID() << " Right face: " << e->Right()->getID() <<
           std::endl;
}

static inline void printFace(std::ostream &out, Face *f) {
    out << "Face: " << f->getID() << std::endl;
    FaceEdgeIterator eitr(f);
    Edge *e = NULL;
    int edge = 0;
    while ((e = eitr.next())) {
        out << "Edge " << edge << " with id: " << e->getID() << " from " <<
               e->Org()->pos << " to " << e->Dest()->pos << std::endl;
        ++edge;
    }
}

static inline void readAndPrintRequest(std::istream &in, std::ostream &out,
                                  Edge *currentEdge) {
    std::string tmp;
    in >> tmp;
    ci_string whatToPrint(tmp.c_str());
    if (whatToPrint == ci_string("current")) {
        printEdge(out,currentEdge);
    } else if (whatToPrint == ci_string("left")) {
        printFace(out,currentEdge->Left());
    } else if (whatToPrint == ci_string("right")) {
        printFace(out,currentEdge->Right());
    } else {
        out << "Unknown print operation requested..." << std::endl;
    }
}

void WalkQuadEdge::interactiveWalk(std::istream &in, std::ostream &out) {
    ci_string input("");
    while (input != ci_string("quit")) {
        if (input == ci_string("print")) {
            readAndPrintRequest(in,out,currentEdge);
        } else if (input == ci_string("go")) {
            currentEdge = readAndGetNextEdge(in, out, currentEdge);
        } else if (input == ci_string("help")) {
            printHelp(out);
        } else if (input.size() > 0) {
            out << "Unknown input... printing help" << std::endl;
            printHelp(out);
        }
        out << std::endl << "> ";
        std::string tmp;
        in >> tmp;
        input = tmp.c_str();
    }
    out << std::endl;
}
