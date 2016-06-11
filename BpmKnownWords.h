// BpmKnownWords.h

#ifndef BPMKNOWNWORDS_H_
#define BPMKNOWNWORDS_H_

/**
 * Containing the bpm average and bpm standard deviation of one known word (the word itself is
 * kept in the static map _bpm of Song)
 */
typedef struct BpmValues
{
	double _average; /**< The average of the bpm word */
	double _deviation; /**< The standard deviation of the bpm word */
} BpmValues;


#endif /* BPMKNOWNWORDS_H_ */
