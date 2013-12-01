#include "Sequences.h"
#include "SequencesKeep.h"

using namespace std;

/*! This static keeper grants that Sequences singleton are created
    before main starts and it is destroyed when the program ends. */
static SequencesKeep keeper;

SequencesKeep::SequencesKeep()
{
    m_seq = Sequences::getInstance();
}

SequencesKeep::~SequencesKeep()
{
    m_seq->destroy();
}

