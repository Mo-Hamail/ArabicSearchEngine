# ArabicSearchEngine ARS
Summary of work Done

Since most Information Retrieval models are mathematically based, the question posed here is: is this sufficient for efficient retrieval of Arabic documents or the model still needs elaboration. To answer these questions, it was necessary to choose and test one of these IR models. Being a one vector-space approach, and a conceptual indexing technique, the Latent Semantic Indexing (LSI) model was chosen. This is because it overcomes the deficiencies of the other models. It achieved up to 30% better retrieval performance than the other techniques.

This project went through two phases. 
	The first was designing and implementing an experimental system based on this model.
	
	The second was measuring the retrieval performance of this system applied to the Arabic
	language, trying to improve its performance. This improvement of the performance involved
	determining the problems faced and trying to handle them using the computational linguistics
	techniques.
  
  An experimental IR system (ARS) was designed and implemented based on the LSI model. It was the first time to apply the LSI retrieval model to Arabic. In order to measure the impact of adding linguistic techniques to the LSI model, three experiments were conducted. The Indexing size was calculated and the retrieval performance was measured using precision, recall and Van Rijsbergen combined measure. 
  
  The first experiment was the core-system (i.e. LSI model only without any linguistic features). In this experiment, the size of indexing was a total of 7.69 MB of the disk space. The retrieval performance resulted in a high precision but a low recall. This means that, only small numbers of relevant documents were retrieved. Two problems aroused which are inflection and synonymy. The system achieved poor retrieval results concerning these two problems. Regarding the query-length, the retrieval performance of the system degraded gracefully as the query length increased. 
  In the second experiment, an attempt to overcome the problem of inflection was made by adding some morphological features to the system using the morphological-normalization technique. In this experiment, the size of indexing was decreased to a 31% of the original size in the first experiment. Expanding the system with the morphological-normalization of keywords led to achieve high levels of precision and recall. Regarding the query length, the retrieval performance of the system decreased as the query length increased, especially for the precision measure. 
  In the third experiment, an attempt to overcome the problem of word synonymy was made by adding some semantic features to the system using semantic-normalization technique. In this experiment, the size of indexing was decreased to 55% of the original size in the first experiment. Expanding the system with the semantic-normalization of keywords compared to the second experiment, led to an increase in recall (i.e. more relevant documents were retrieved) for an insubstantial average decrease in precision. Regarding the query length, the retrieval performance of the system decreased as the query length increased, especially for the precision measure. Finally, the model was evaluated in the light of the results of the three experiments.
