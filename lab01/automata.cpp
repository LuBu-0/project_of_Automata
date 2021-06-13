#include "automata.h"
#include <iostream>

using namespace std;

/**
 * Constructor for Abstract DFA.
 *
 * @param noStates
 *            Number of states in the DFA.
 */
AbstractDFA::AbstractDFA(int noStates)
    : noStates(noStates), currentState(initState) {}
// Build and initialize noStates and currentStates of *this

/**
 * Reset the automaton to the initial state.
 */
void AbstractDFA::reset() { currentState = initState; }
// Bring back the DFA to the initial state

/**
 * Performs one step of the DFA for a given letter. If there is a transition
 * for the given letter, then the automaton proceeds to the successor state.
 * Otherwise it goes to the sink state. By construction it will stay in the
 * sink for every input letter.
 *
 * @param letter
 *            The current input.
 */
void AbstractDFA::doStep(char letter) {
  // If the DFA is in the trapState, it will remain there
  if (currentState != trapState) {
    map<tpair, int>::iterator it =
        transitionFunc.find(tpair(currentState, letter));
    // Check if the currentState has an exiting transition which consumes the
    //  input letter
    if (it != transitionFunc.end()) {
      // If a valid transition is found, the DFA move to the next state
      currentState = it->second;
    } else {
      // Else it falls in the sink state
      currentState = trapState;
    }
  }
}

/**
 * Check if the automaton is currently accepting.
 *
 * @return True, if the automaton is currently in the accepting state.
 */
bool AbstractDFA::isAccepting() {
  // checks if currentState is a final state
  return finalStates.find(currentState) != finalStates.end();
}

/**
 * Run the DFA on the input.
 *
 * @param inputWord
 *            stream that contains the input word
 * @return True, if if the word is accepted by this automaton
 */
bool AbstractDFA::run(const string &inputWord) {
  this->reset();
  for (int i = 0; i < inputWord.length(); i++) {
    doStep(inputWord[i]);
  }
  return isAccepting();
}

/**
 * Construct a new DFA that recognizes exactly the given word. Given a word
 * "foo" the constructed automaton looks like: -> () -f-> () -o-> () -o-> []
 * from every state (including the final one) every other input letter leads
 * to a distinguished sink state in which the automaton then remains
 *
 * @param word
 *            A String that the automaton should recognize
 */
WordDFA::WordDFA(const string &word) : AbstractDFA(word.length() + 1) {
  // This DFA has a state for each leading substring of the input word
  // If currentState != trapState then the DFA has consumed
  //  word[0..currentState-1]
  // It reach the final state iff it has consumed word[0..word.length()-1]
  //  which means currentState == word.length()
  for (int i = 0; i < word.length(); ++i) {
    transitionFunc.insert(pair<tpair, int>(tpair(i, word[i]), i + 1));
  }
  finalStates.insert(word.length());
}

/**
 * Construct a new DFA that recognizes comments within source code. There
 * are three kinds of comments: single line comment that starts with // and ends
 * with a newline, multiline comments that starts with (* and ends with *), and
 * multiline comments that starts with { and ends with }
 */
CommentDFA::CommentDFA() : AbstractDFA(8) {
  // This DFA reproduce the automaton which can be found at
  //https://github.com/matnut2/AutomataLab1/blob/Master/Varie/comment.jff
  // It has three branches, one for each type of comment.
  // Some transitions are hard-coded in doStep to avoid the insertion of about a
  //  thousand of transitions in transitionFunc.
  transitionFunc.insert(pair<tpair, int>(tpair(0, '/'), 1));
  transitionFunc.insert(pair<tpair, int>(tpair(1, '/'), 2));
  // Self-loop on state 2 hard coded in doStep
  transitionFunc.insert(pair<tpair, int>(tpair(2, '\n'), 3));
  transitionFunc.insert(pair<tpair, int>(tpair(0, '{'), 4));
  // Self-loop on state 4 hard coded in doStep
  transitionFunc.insert(pair<tpair, int>(tpair(4, '}'), 3));
  transitionFunc.insert(pair<tpair, int>(tpair(0, '('), 5));
  transitionFunc.insert(pair<tpair, int>(tpair(5, '*'), 6));
  // Transictions starting from state 6 hard coded in doStep
  // Transictions starting from state 7 hard coded in doStep
  transitionFunc.insert(pair<tpair, int>(tpair(7, ')'), 3));
  finalStates.insert(3);
}

/**
 * Performs one step of the DFA for a given letter. This method works
 * differently than in the superclass AbstractDFA.
 *
 * @param letter
 *            The current input.
 */
void CommentDFA::doStep(char letter) {
  switch (currentState) {
  case 2:
    if (letter == '\n') {
      currentState = 3;
    }
    break;
  case 4:
    if (letter == '}') {
      currentState = 3;
    }
    break;
  case 6:
    if (letter == '*') {
      currentState = 7;
    }
    break;
  case 7:
    if (letter == ')') {
      currentState = 3;
    } else if (letter != '*') {
      currentState = 6;
    }
    break;
  default:
    AbstractDFA::doStep(letter);
    break;
  }
}
