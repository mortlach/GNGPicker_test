![Image]{./assets/img/Profile.jpeg}

Liber Primus 

(Feel free to play with this app, check it works, report issues, try and break it, any ideas?)

****************************************** 
In its current form the app has most of the main features implemented or close to implemented, but the full word lists of raw data have not been shared with the app. Only phrases that can be made with words from files in ./data/n_grams can be used to generate a new phrase. 
****************************************** 

• Overview

Cribbing is the art of "guessing the plaintext." The purpose of the app is to help cribbing phrases from the LP. At it's most basic level it is a tool to find combinations of words that ***make sense to you***    

It takes various sets of plaintext wordslists and rune data from the Liber Primus, saved in human readable formats, and provides an interface to allow for easy manual cutting and selecting of different words and automated rationlizing of those choices accross the entire dataset wordlists. As the raw data is contained in human readable files they allow for offline processing or use in other apps as well as some degree of customization of the  based on your preferences.   

The Liber Primus will normally be denoted as LP. 

As  a brief introduction a summary of how 565.jpg can be solved, more detail cna be found here:

The last solved page of the LP, 56.jpg, (first solved in May 2014) can be decrypted using a few basic assumptions on how runes "work", a pre-computed word list, brute force methods and spotting a pattern. The basic assumptions include: we can asume we know the word lengths in runes and the sentence lengths in words. Also, the plaintext is in runeglish, i.e natural language written english, converted to runes using the rules taught in the gematria primus and the results of previously decrypted pages.

56.jpg starts with 2 runewords of length 2 and 3: ᚫᛂ ᛟᛋᚱ. To help guess what these words might be, we can compile a list of all the words that are 2 and 3 runes long by converting an existing list of words into runes and filtering out words of the correct length. It happens that the lists of common words that are only two and three runes length are not that long and so it is possible to make a list of all possible combinations of 2 then 3 rune words. It is very resonable to assume that the correct, decrypted plaintext is contained within this list. We can try these guesses in decryption functions and look at the keys that would have to be used to create the cipher text of the LP. When we do this for the encryption function ciphertext = plaintext + key replacing runes by their numerical position in the gematria primus there is one key that stands-out under inspection, 1,2,4,6,10  this, you may notice, is the prime sequence - 1. When we try extending this sequence and using it as the key we get more readable plaintext. A solution has been found! 

In principle the above method should work on many different types of encryption, and we should try it on the unsolved parts of the LP. When we do this we encounter some issues with many parts of the LP that hinder us. These include the vast number of possible words there are, and the even vaster number of possible ways of combining those words. For 56.jpg we were fortunate (or was it a planned wekaness??) that the number of combinations of 2 then 3 rune words was not too great, as low as a few thousand. For other rune lengths, and phrases with more than two words it is easy to have millions of possibilities. To proceed with this technique we need better methods to generate the possible plaintext words. An obvious answer is to only allow actual phrases that make sense in natural language.

This can be done by guessing what the phrase is yourself. Perhaps instead of usign the brute force approach to 56.jpg you can look at the words lists and guess combintions that make sense to you. Or perhaps you do generate all combinations of 2 then 3 rune words and then read through those to pick out the ones that make sense to you and seem plausible text for the LP. At it's most basic level, this app is to help you find combinations of words that match the assumptions and make sense to you. It does this by providing a graphical interface to a ast list of initial words chosen from natural language sources by google. Your task is to cut the word lists down based on what you think could plausibley be  written. You can do this by selecting words from the main list of possible words, or from lists of possible combinations of the words. As this is a new tool there will be more ways to use it than i will describe here, an overview of the main concepts will be given and then an initial way to startup fairly quickly. 

Before we start, a warning, the google data is big. Really big. You just won't believe how vastly, hugely, mind-boggling big it is. I mean, you may think it's a long way down the road to the chemist, but that's just peanuts to google... This is on purpose. In many ways this app has been on proto-devlopement for years, and, hopefully this will be the end of that developmemnt process. Therefore, after consideration it was felt that starting from a large base of initial words provides the best base. Once the cuts to the main word list hav ebeen made they can be re-used forever.  Its also simpoel to import lisst from other from other solvers. The app has been designed in such a way that difeferent word lists can easily substituted in. 
   

Some Basic definitions.

Sentences from the LP are defined in ./data/lp_sents_2022.txt  
examples:
ᛋᚻᛖᚩᚷᛗᛡᚠ ᛋᚣᛖᛝᚳ
ᚦᛂᚷᚫ ᚠᛂᛟ ᚩᚾᚦ ᚾᛖᚹᛒᚪᛋᛟᛇᛁᛝᚢ ᚾᚫᚷᛁᚦ ᚻᛒᚾᛡ ᛈᛒᚾ ᛇᛂᚦ ᚪᛝᚣᛉ ᛒᛞᛈ ᛖᛡᚠᛉᚷᚠ ᛋᛈᛏᚠᛈᚢᛝᚣᛝᛉᛡ ᚣᚻ ᛒᚢ ᚷᚩᛈ ᛝᚫᚦ ᛁᚫᚻᛉᚦᛈᚷ ᚣᚠᛝᚳᛂ ᚦᚪᛗᛁᛝᛁᛡᚣ ᚻᛇ ᛏᚻᚫᛡ ᛉᚣ ᛖᚢᛝ ᚳᚠᚾ ᛇᚦᛂᛁᚦ ᚦᛈ ᚣᛝᛠ ᚣᚾᛖᚣ ᛞᛉᛝᚹ ᛒᚳᛉᛞᛒᚠ ᛗᛏᚾᛖ ᛠᛂᚾᛚᚷᛒ ᛉᚷᚦ

A Phrase is a group of at least two consecutive words that are wholly contained within a sentence of the LP. The maximum length of a phrase is the number of words in the sentence.
ᛋᚻᛖᚩᚷᛗᛡᚠ ᛋᚣᛖᛝᚳ
ᛡᛞᛈᛝᚢᚹᚪᛗ ᛏᚪᛝ ᛝᚦᛡᚹᛋᚻ ᛁᚳ ᚫᛈᚫᚷᚩ ᛗᛁᚪ ᛖᚩ ᛏᚹᚩ ᚠᚣᚢᛏᛂ


As well as words a phrase contains and N-grams.  

An N-gram is a group of N consecutive words, using the example "for all is sacred" the n-grams are:
1-grams 
"For", "all", "that", "lives", "is", "sacred" 
2-grams
"For all", "all that", "that lives", "lives is", "is sacred" 
3-grams
"For all that", "all that lives", "that lives is", "live is sacred" 
etc. 

The n-grams from google (https://storage.googleapis.com/books/ngrams/books/datasetsv3.html)
have been converted to runes and placed in files based on the rune counts for each word in the n-gram. 

Main 1-grams 
This is a list of all the unique words from the google data, divided into files for each rune count (all 1 rune swords, 2 rune words, 3 rune words etc.)

Once an LP phrase has been chosen the relevant n-grams from the google data can be used. For the phrase, and looking at 2-grams "ᛡᛞᛈᛝᚢᚹᚪᛗ ᛏᚪᛝ ᛝᚦᛡᚹᛋᚻ ᛁᚳ ᚫᛈᚫᚷᚩ" data with these word legths are required: 8 3, 3 6, 6 2, 2 5

Phrase Unique Words. From the ngram data we can get the unique words fro each word in the phrase, continuing the above example, these would be the unique 8 runes words in the 8 3 data, the unique words from the combined set of 3 rune words in the 8 3 data and the 3 6 data, the unique words from the combined set of 6 rune words in the 3 6 data and the 6 2 data, etc. 

As words with the same length can occur more than once in a phrase there is also the set of the unique words for each unique word length. This data is avialable in the app but is not yet currently integrated with the rest of the data.  

Each tab on the app shows an interactive table of different sets of words lists, for the main-1-grams, the LP sentences, the phrase n-grams and phrase unique words. To the left are controls for saving all files, loading a phrase, create a new phrase, rationalize an existing phrase, set ++n-grams checkbox. 

Word list tables.
These display the word lists and associated meta data. Meta data includes word in runes and english, gematria sum of word, count in google n-gram data, chosen status etc. Tables are interactive, they can can be sorted by column headers and filtered by chosen, not chosen and all words. These features are to help with the main task, choosing the words you think are, or are not in the Liber Primus. The chosen / not chosen status can be set by selecting a row or rows and double clicking, pressing left space bar, alt+t to set chosen or alt+f to set not chosen. All rows  can be selected with ctr+a. Data can be saved, overwriting the current savefile with the existing in app state, or loaded overwriting the exisiting in app state with the savefaile data. 
There is a text entry box and button to find a particular string in the data.
The delete button permanently deletes not chosen entries from the in app data set. They cannot be recovered (saved data can always be reloaded). This feature can be really useful for reducing the data you want to work with.         

For now the above is the basics, particular tabs have unique features under development and being implemented that may or may not work. 

On startup the app loads in the main-1-grams. This is a good place to learn the basics. The first table is the unique words with 1 rune from the google n-gram data. There are apparently over 29 words with 1 rune in the ggogle data, how can this be? It's because we're dealing with a very large dataset from google, and a very relaxed inital cut to that dataset when it was converted into runes. LINK to git. With some patience (!) and a bit of time it won't take that long to reduce the words i think most humans would easily cut from these lists. Plus word lists can easily be shared and copied in so hopefully over time there will be community based lists availble.

now start using the app and explain what is going on 

need to add features to explain it and improve gui to make it work 



   








How to choose in general. 







How to choose the Main 1-grams

  





How to choose a Phrase 





Data taken from google ngrams 

• Installation / setup
• Code structiure