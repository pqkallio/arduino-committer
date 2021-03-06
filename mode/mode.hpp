#ifndef _COMMITTER_MODE_HPP
#define _COMMITTER_MODE_HPP

/**
 * An interface to be implemented by all specific execution modes.
 */
class ModeInterface {
public:
  /**
   * Called when the mode is entered.
   */
  virtual void onEnter() = 0;

  /**
   * Called in each loop.
   * Must return {this} or the following mode.
   */
  virtual ModeInterface* tick(unsigned long currentTime) = 0;
};

#endif /* _COMMITTER_MODE_HPP */
