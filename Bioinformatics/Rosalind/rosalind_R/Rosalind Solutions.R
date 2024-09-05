library(stringr)
library(stringi)
library(dplyr)

setwd("~/OneDrive/Documents/Programming/Rosalind")

dna.bases = c('A', 'C', 'G', 'T')
rna.bases = c('A', 'C', 'G', 'U')

codon.aa = scan('codon_to_aa.txt', what = 'character')

odd = seq(1,length(codon.aa),2)
even = seq(2,length(codon.aa),2)

aa_by_codon = codon.aa[even]
names(aa_by_codon) <- codon.aa[odd] # amazing alternative to dictionary

# 1 - 	Counting DNA Nucleotides
s1 = scan(file = 'rosalind_dna.txt', what = 'character')

str_count(s1, dna.bases)

# 2 - Transcribing DNA into RNA
s2 = scan(file = 'rosalind_rna.txt', what = 'character')

rna.s2 = str_replace_all(s2, 'T', 'U')
rna.s2

# 3 - Complementing a Strand of DNA
s3 = scan(file  = 'rosalind_revc.txt', what = 'character')
s3.rev = stringi::stri_reverse(s3)

s3.c = s3.rev %>% 
  str_replace_all(c('A' = 't', 'C' = 'g', 'G' = 'C', 'T' = 'A')) %>%
  str_to_upper()
s3.c

# 4 - Rabbits and Recurrence Relations
fib = function(n){ # returns the nth Fibonacci number
  if (n==0) return(0);
  if (n==1) return(1);
  ifelse(n>2, fib(n-1) + fib(n-2), 1)
}

wabbit = function(n, k){
  if (n==0) return(0);
  if (n==1) return(1);
  ifelse(n>2, wabbit(n-1, k) + k*wabbit(n-2, k), 1)
}

megawab = wabbit(3, 5)

# 5 - Computing GC Content
s5 = str_flatten(scan(file = 'rosalind_gc.txt', what = 'character'))

s5.labels = s5 %>%
  str_split('>', simplify = TRUE) %>%
  str_extract('Rosalind_[0-9]*') # want to say 'all characters from the start up to
                                  # and including the last number'

s5.strings = s5 %>%
  str_split('>', simplify = TRUE) %>% # simplify=TRUE lets it pass into str_extract
  str_extract('(?<=[0-9]{4}).*$')

s5.GC = str_count(s5.strings, 'G|C')/str_length(s5.strings)

GC.df = data.frame(ID = s5.labels,
                   GC_percent = s5.GC*100)
GC.df[which.max(s5.GC),]

#6 - Counting Point Mutations
s6 = scan('rosalind_hamm.txt', what = 'character') 

s = s6[1]
t = s6[2]

d_h = function(s,t){
  d = 0
  for (i in (1:str_length(s))){
    if (str_sub(s, i, i) == str_sub(t, i, i)){d <- d+1}
  }
  str_length(s) - d
}

# 7 - Mendel's First Law
n = 29 # homozygous dominant
m = 15 # heterozygous
k = 20 # homozygous recessive
pop = n+m+k

p.AA = n/pop
p.Aa = m/pop
p.aa = k/pop

p_dom = p.AA*((n-1)/(pop-1)) + p.AA*(m/(pop-1)) + (n/(pop-1))*p.Aa + 
  (n/(pop-1))*p.aa + p.AA*(k/(pop-1)) + (m/(pop-1))*p.aa*0.5 + 
  p.Aa*(k/(pop-1))*0.5 + p.Aa*((m-1)/(pop-1))*0.75 

#8 - Translating RNA into Protein
s8 = scan('rosalind_prot.txt', what = 'character')

s8.codons = c()
for(base in seq(1,str_length(s8), 3)){
  s8.codons = c(s8.codons, str_sub(s8, base, base+2))
}

s8.aa = str_flatten(aa_by_codon[s8.codons]) %>%
  str_extract('^.*(?=Stop)')

#9 - Finding a Motif in DNA
s9 = scan('rosalind_subs.txt', what = 'character')
s9.seq = s9[1]
s9.match = paste0("(?=(", s9[2], "))")  
      # e.g. '(?=(ATAT))' i.e followed by ATAT
      # this is a zero-length match which checks each character and hence 
      # does not consume the string 
      # {as opposed to 'ATAT' which has length of 4 and checks in intervals of 4}

s9.matches = str_locate_all(s9.seq, s9.match) 
s9.matches.start = sapply(s9.matches, function(x){x[,1]})[,1] 
  # this generalises if finding matches to multiples strings in s9
s9.matches.start

# 10 - Consensus and Profile
s10 = 

# 11 - Mortal Fibonacci Rabbits~~~~~~~~~~~~~~~~~~~~~~~~~~~
ded = function(n,m){
  if (n==0) return(0);
  if (n==1) return(1);
  ifelse(n>2, 
         ifelse(n-m > 0, 
                ded(n-1, m) + ded(n-2, m) - ded(n-m, m), 
                ded(n-1, m) + ded(n-2, m)), 
         1)
}


