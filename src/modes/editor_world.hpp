#ifndef EDITOR_WORLD_H
#define EDITOR_WORLD_H

#include <vector>

#include "modes/world_with_rank.hpp"
#include "utils/aligned_array.hpp"

#include "LinearMath/btTransform.h"

class EditorWorld : public WorldWithRank
{
protected:

    /** Override from base class */
    virtual void  createRaceGUI();

    bool m_return_to_garage;

public:
                  EditorWorld();
    virtual      ~EditorWorld();

    static void enterEditorWorld();

    virtual void  update(float delta) OVERRIDE;
    virtual void  getKartsDisplayInfo(
                 std::vector<RaceGUIBase::KartIconDisplayInfo> *info) OVERRIDE;
    // ------------------------------------------------------------------------
    /** Returns if this race mode has laps. */
    virtual bool  raceHasLaps() OVERRIDE { return false; }
    // ------------------------------------------------------------------------
    /** The overworld is not a race per se so it's never over */
    virtual bool    isRaceOver() OVERRIDE { return false; }
    // ------------------------------------------------------------------------
    /** Implement base class method */
    virtual const std::string&
                    getIdent() const OVERRIDE { return IDENT_OVERWORLD; }
    // ------------------------------------------------------------------------
    /** Override base class method */
    virtual bool shouldDrawTimer() const OVERRIDE { return false; }
    // ------------------------------------------------------------------------
    /** Override base class method */
    virtual void onFirePressed(Controller* who) OVERRIDE;
    // ------------------------------------------------------------------------
    /** Override settings from base class */
    virtual bool useChecklineRequirements() const OVERRIDE { return false; }
    // ------------------------------------------------------------------------
    void scheduleSelectKart() { m_return_to_garage = true; }
    // ------------------------------------------------------------------------
    virtual void onMouseClick(int x, int y) OVERRIDE;
};

#endif // EDITOR_WORLD_H
