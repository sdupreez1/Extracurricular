from Bio.Seq import Seq, translate
from Bio import Entrez, SeqIO 
from Bio.Data import CodonTable
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

# 5 - Pairwise Global Alignment (Emboss Scoring Matricies) [Online - Emboss]
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

# 8 - Protein Translation (Using Different Translation Tables)
with open('data/rosalind_ptra.txt') as str_prt:    
    s8 = str_prt.read().split('\n')
    prt8 = s8[1]
    s8 = s8[0]

table_ids = [id_num for id_num in sorted(CodonTable.generic_by_id)]

for table_id in table_ids: # There are currently 33 tables as of 02/09/2024
    match_point = [(match.start() for match 
                       in list(re.finditer(prt8, translate(s8, table_id))))]
    if bool(match_point) == True:
        print(table_id, match_point, translate(s8, table_id))

# 9 - Read Filtration by Quality (Filter Better Quality Reads) 
#     [Online - Galaxy for FastQC]
with (open('data/rosalind_filt.txt') as infile9,
      open('data/rosalind_fastqual.txt', 'w') as outfile9):
    # crit9 = re.findall('^.*(?=\n)', all9)[0].split()  # Look for better method
    crit9 = infile9.readline().strip().split()  
        # readline() 'consumes' the first line
    outfile9.write(infile9.read()) 
        # read() 'consumes' the remaining text (without the first line since 
        # it's been used in readline() above)

# 10 - Complementing a Strand of DNA
with open('data/rosalind_rvco.txt') as infile10:
    seq10 = list(SeqIO.parse(infile10, 'fasta'))
    seq10 = [s.seq for s in seq10]
    rev_comp10 = [s.reverse_complement() for s in seq10]
    rev_same10 = [s for s in seq10 if rev_comp10[seq10.index(s)] == s]
len(rev_same10)
    
# 12 - Base Quality Distrtibution
with open('data/rosalind_bphr.txt') as infile12:
    crit12, fastq12 = infile12.readline(), infile12.read()
    open('data/test_fastq.txt', 'w').write(fastq12)
    
    records12 = list(SeqIO.parse('data/test_fastq.txt', 'fastq'))
    phd_list12 = [s.letter_annotations['phred_quality'] for s in records12]
    phd_bybase12 = [base for phds in phd_list12 for base in phds]
    phd_avg12 = [
        mean([p[i] for p in phd_list12]) for i in range(len(phd_list12[0]))
        ]
    invalid_phds12 = [base for base in phd_avg12 if base < int(crit12)]
len(invalid_phds12)

# 14 - Finding Genes with ORFs (Open Reading Frames) [Online - SMS2]
with open('data/test.txt') as infile14:
    prts14 = infile14.readlines()
    prtlens14 = list(map(len, prts14))
    whichlong14 = prtlens14.index(max(prtlens14))
print(prts14[whichlong14])
