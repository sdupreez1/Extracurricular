from Bio.Seq import Seq
from Bio import Entrez, SeqIO
import pandas as pd

pd.options.display.width = 0

# 1 - Introduction to the Bioinformatics Armory
dna_bases = ['A', 'C', 'G', 'T']

s1 = Seq(open('data/rosalind_ini.txt').read())
s1_counts = [s1.count(base) for base in dna_bases]

# 2 - GenBank Introduciton (Searching for data in GenBank using Entrez)
Entrez.email = 'sethdupreez@gmail.com' 
    # Email so I can be contacted by NCBI if there is a problem

queries2 = open('data/rosalind_gbk.txt', 'r').read().split()

handle2 = Entrez.esearch(
    db='nucleotide', 
    term='"{}"[Organism] AND ("{}"[PDAT]: "{}"[PDAT])'.format(*queries2)
    )
record2 = Entrez.read(handle2)
record2['Count']

# 3 - Data Formats (Using SeqIO to deal with Entrez data)
ids3 = open('data/rosalind_frmt.txt').read().split()
handle3 = Entrez.efetch(db='nucleotide', id=ids3, rettype='fasta')

records3 = list(SeqIO.parse(handle3, 'fasta'))

seqlens3 = [len(s.seq) for s in records3]
whichmin3 = seqlens3.index(min(seqlens3))
minseq3 = records3[whichmin3]

fastamin3 = '>{}\n{}'.format(minseq3.description, minseq3.seq)

# 5 - Pairwise Global Alignment (Emboss Scoring Matricies)
ids5 = open('data/rosalind_need.txt').read().split()
handle5 = Entrez.efetch(
    db='nucleotide',
    id=ids5,
    rettype='fasta'
    )
records5 = list(SeqIO.parse(handle5, 'fasta'))
seq5 = [s.seq for s in records5]

open('data/emboss_string1.txt', 'w').write(str(seq5[0]))
open('data/emboss_string2.txt', 'w').write(str(seq5[1]))

# 6 - FASTQ format introduction (FASTQ to FASTA conversion)
fastq_in6 = open('data/rosalind_tfsq.txt', 'r')
fasta_out6 = open('data/fastq2fasta.txt', 'w')

fasta_out6 = SeqIO.convert(
    fastq_in6, 'fastq', 
    fasta_out6, 'fasta'
    )
