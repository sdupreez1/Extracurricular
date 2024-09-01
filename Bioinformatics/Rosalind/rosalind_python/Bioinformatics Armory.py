from Bio.Seq import Seq
from Bio import Entrez, SeqIO #can't import translate?
import re

# 1 - Introduction to the Bioinformatics Armory
dna_bases = ['A', 'C', 'G', 'T']

with open('data/rosalind_ini.txt') as seqfile1:
    s1 = Seq(seqfile1.read())
    s1_counts = [s1.count(base) for base in dna_bases]

# 2 - GenBank Introduciton (Searching for data in GenBank using Entrez)
Entrez.email = 'sethdupreez@gmail.com' 
    # Email so I can be contacted by NCBI if there is a problem

with open('data/rosalind_gbk.txt') as querfile2:
    queries2 = querfile2.read().split()
    handle2 = Entrez.esearch(
        db='nucleotide', 
        term='"{}"[Organism] AND ("{}"[PDAT]: "{}"[PDAT])'.format(*queries2)
        )
    record2 = Entrez.read(handle2)
    record2['Count']

# 3 - Data Formats (Using SeqIO to deal with Entrez data)
with open('data/rosalind_frmt.txt') as idfile3:
    ids3 = idfile3.read().split()
    handle3 = Entrez.efetch(db='nucleotide', id=ids3, rettype='fasta')
    
    records3 = list(SeqIO.parse(handle3, 'fasta'))
    
    seqlens3 = [len(s.seq) for s in records3]
    whichmin3 = seqlens3.index(min(seqlens3))
    minseq3 = records3[whichmin3]
    
    fastamin3 = '>{}\n{}'.format(minseq3.description, minseq3.seq)

# 5 - Pairwise Global Alignment (Emboss Scoring Matricies)
with open('data/rosalind_need.txt') as idfile5:
    ids5 = idfile5.read().split()
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
with open('data/fastq2fasta.txt', 'w') as fasta_out6:
        SeqIO.convert(
            'data/rosalind_tfsq.txt', 'fastq', 
            fasta_out6, 'fasta'
            )

# 7 - Read Quality Distribution (Phred Quaility)
with (open('data/rosalind_phre.txt') as infile, 
      open('data/phre2fastq.txt', 'w') as fastq_in):
        fullfile = infile.read()
        phd_thresh7 = re.findall('^[0-9]+(?=\n)', fullfile)[0]
        fastq_sect = fullfile.lstrip(phd_thresh7 + '\n')
            # regex says from the start only (^), match one or more (+) 
            # digits ([0-9]) followed by a newline ((?=\n))
        fastq_in.write(fastq_sect)
        records7 = list(SeqIO.parse('data/phre2fastq.txt', 'fastq'))
        phds7 = [s.letter_annotations['phred_quality'] for s in records7]

def mean(ls):
    return sum(ls)/len(ls)

phds_avg7 = [mean(phd) for phd in phds7]
phds_low7 = [phd for phd in phds_avg7 if phd<float(phd_thresh7)]

# 8 - Protein Translation
with open('data/codon_to_aa.txt', 'r') as transl_table:
    rna_to_aa = transl_table.read().split()
    rna_to_aa = {cdn:aa for cdn, aa in zip(rna_to_aa[::2], rna_to_aa[1::2])}

dna_bases = ['A', 'C', 'G', 'T']
dna_to_rna = {'A':'u', 'C':'g', 'G':'c', 'T':'a'}

with open('data/rosalind_ptra.txt') as str_prt:    
    s8 = str_prt.read().split('\n')
    prt8 = s8[1]
    s8 = s8[0]

def transcribe(s):
    for base in dna_bases:
        s = s.replace(base, dna_to_rna[base])
    s = s.upper()
    return s

def translate(s):
    return ''.join([
        rna_to_aa[codon] for codon in  list(map(''.join, zip(*[iter(s)]*3)))
        ])

transl8 = translate(transcribe(s8))
[match.start() for match in list(re.finditer(prt8, transl8))]
