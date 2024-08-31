from Bio.Seq import Seq
from Bio import Entrez, SeqIO
import pandas as pd
import os

pd.options.display.width = 0

# Allows me to access data folder within project working directory
path = os.path.realpath(__file__)
dir = os.path.dirname(path)
dir = dir+'\data\\'
os.chdir(dir)

# 1 - Introduction to the Bioinformatics Armory
dna_bases = ['A', 'C', 'G', 'T']

s1 = Seq(open('rosalind_ini.txt').read())
s1_counts = [s1.count(base) for base in dna_bases]

# 2 - GenBank Introduciton
Entrez.email = 'sethdupreez@gmail.com' 
    # Email so I can be contacted by NCBI if there is a problem

queries2 = open('rosalind_gbk.txt', 'r').read().split()

handle2 = Entrez.esearch(
    db='nucleotide', 
    term='"{}"[Organism] AND ("{}"[PDAT]: "{}"[PDAT])'.format(*queries2)
    )
record2 = Entrez.read(handle2)
record2['Count']

# 3 - Data Formats
ids3 = open('rosalind_frmt.txt').read().split()
handle3 = Entrez.efetch(db='nucleotide', id=ids3, rettype='fasta')

records3 = list(SeqIO.parse(handle3, 'fasta'))

seqlens3 = [len(s.seq) for s in records3]
whichmin3 = seqlens3.index(min(seqlens3))
minseq3 = records3[whichmin3]

fastamin3 = '>{}\n{}'.format(minseq3.description, minseq3.seq)
