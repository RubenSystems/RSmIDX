

# import tensorflow as tf
# from transformers import BertTokenizer, TFBertModel

# tokenizer = BertTokenizer.from_pretrained('bert-base-uncased')
# model = TFBertModel.from_pretrained('bert-base-uncased')
# input_ids = tf.constant(tokenizer.encode("Hello, my dog is cute"))[None, :]  # Batch size 1
# print("start")
# outputs = model(input_ids)
# last_hidden_states = outputs[0]  # The last hidden-state is the first element of the output tuple

# print(last_hidden_states)

import rsmidx
import time
import cPickle as pickle

indexConfig = rsmidx.IndexConfig("index", 100000, [ "sitename" ], (128, 4, 384))
index = rsmidx.Index(indexConfig)
index.unarchive()

from sentence_transformers import SentenceTransformer
model = SentenceTransformer('paraphrase-MiniLM-L12-v2')
sentences = ['This framework generates embeddings for each input sentence',
    'Sentences are passed as a list of string.', 
    'The quick brown fox jumps over the lazy dog.']
sentence_embeddings = model.encode(sentences)
for i in range(len(sentence_embeddings)):
	page = rsmidx.Page(sentences[i], {"text": sentences[i], "sitename": "testsite"}, [sentence_embeddings[i].T])
	index.add(page)


print([x.data().metadata["text"] for x in index.getSimilar([sentence_embeddings[2].T])])

start_time = time.time()
index.archive()
print("--- %s seconds ---" % (time.time() - start_time))